#include <iostream>
#include "ComputeEngine.h"
#include "GraphAlgorithms.h"
#include "Name.h"
#include "Plug.h"
#include "Edge.h"
#include "Context.h"

#include <llvm/Constants.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/IRBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/DataLayout.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Linker.h>



using namespace fission;
using llvm::getGlobalContext;
using llvm::Function;
using llvm::FunctionType;
using llvm::BasicBlock;


llvm::Value *
ComputeEngine::buildContext(const Context &context)
{
    // Make a constant from the context stored in a global variable
    llvm::StructType *ctxType = m_llvmModule.getTypeByName ("class.fission::Context");
    // Note : get pointer type from a type
    //llvm::PointerType *const ctxTypePtr = llvm::PointerType::getUnqual( ctxType );
    if(ctxType==0) {
        std::cout << "Context type not found" << std::endl;
        exit(0);
    }

    // Pass values to jitted code
    // 2 methods : define constant value, which can be folded
    //             define a mapping to a instance of the value
    // The constant value allows further optimization
#define USE_CONSTANT 0
#if USE_CONSTANT
    llvm::Constant *res = llvm::ConstantStruct::get(ctxType
                    , m_builder->getInt32(context.m_first)
                    , m_builder->getInt32(context.m_last)
                    , NULL );
    llvm::GlobalVariable *glob = new llvm::GlobalVariable( m_llvmModule
                                , ctxType
                                , true
                                , llvm::GlobalValue::InternalLinkage
                                , res);
#else
    // Use external variable
    llvm::GlobalVariable *glob = new llvm::GlobalVariable( m_llvmModule
                                , ctxType
                                , false // is constant
                                , llvm::GlobalValue::ExternalLinkage
                                , NULL);
    m_engine->addGlobalMapping(glob, (void *)&context);
#endif
    return glob;
}


/// Recursively build the call graph from the node graph
llvm::Value *
ComputeEngine::buildCallGraphRecursively(
      Plug *plug
    , llvm::Value *context)
{
    llvm::Module &module = m_llvmModule;
    llvm::IRBuilder<> &builder = *m_builder;
    if(IsOutput(plug)) {
        // iterate on args,
        // Look up the name in the global module table.
        std::string Callee(std::string(TypeName(Owner(plug))) + "_execute");
        llvm::Function *CalleeF = module.getFunction(Callee);
        if (CalleeF == 0) {
            m_llvmModule.dump();
            std::cout << "ERROR Function " << Callee << " not found" << std::endl;
            exit(0);
        } else {
            std::cout << "Function " << Callee << " found" << std::endl;
        }

        // TODO :Optimize function
        // check clang -O3 passes
        // m_funcPassManager->run(*CalleeF);

        // debug
        // std::cout << "====Fun: \n";
        //CalleeF->getFunctionType()->getParamType(0)->dump() ;
        // std::cout << "====\n";

        const size_t nbArgs = NbConnectedInputs(plug);
        std::vector<llvm::Value*> ArgsV(nbArgs+1);
        GraphIterator<Plug, PlugLink> it(plug);

        // First argument of all function is the context
        ArgsV[0] = context;

        // The other arguments are built recursively
        for (unsigned int i=1; i < nbArgs+1; ++i, ++it) {
            ArgsV[i] = buildCallGraphRecursively(it.nextVertex(), context);
        }
        std::cout << "Create call " << Name(Owner(plug)) << "_tmp" << std::endl;
        llvm::Value *ret=builder.CreateCall(CalleeF, ArgsV, Name(Owner(plug))+"_tmp");
        return ret;

    } else if(IsInput(plug)) {
        const size_t nbConnections = NbConnectedInputs(plug);
        if (nbConnections==0) {
            // recursive call
            // Create a dummy value
            assert(0); // shouldn't happen with the current setup
            return NULL;
        } else {
            // only one connection allowed
            assert(nbConnections==1);
            GraphIterator<Plug, PlugLink> n(plug);
            return buildCallGraphRecursively(n.nextVertex(), context);
        }

    } else {
        // ERROR !!
        return NULL;
    }

    return NULL;
}


/// Build and ast starting at plug
llvm::Value *
ComputeEngine::buildCallGraph(
      Plug *plug
    , const Context &context)
{
    std::string funcName("ComputeEngine::runonce");

    // Create a function and a building block
    std::vector<llvm::Type*> argsProto;
    FunctionType *FT = FunctionType::get(
            llvm::Type::getDoubleTy(getGlobalContext()), // Return type
            argsProto,                                   // Arguments type
            false);
    Function *F = Function::Create(
            FT,         // Function type
            llvm::Function::ExternalLinkage,
            funcName,
            &m_llvmModule);

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    m_builder->SetInsertPoint(BB);
    llvm::Value *ctxVal = buildContext(context);

    m_builder->CreateRet(buildCallGraphRecursively(plug, ctxVal));
    llvm::verifyFunction(*F);
    return 0;
}

// Constructor
ComputeEngine::ComputeEngine(Module &fissionModule)
: m_module(fissionModule)
, m_llvmModule(*fissionModule.m_llvmLinker->getModule())
, m_passManager(new llvm::PassManager())
, m_funcPassManager(new llvm::FunctionPassManager(&m_llvmModule))
, m_engine(0)
, m_engineErrStr("")
, m_builder(0)
{
    m_builder=new llvm::IRBuilder<>(llvm::getGlobalContext());

    m_engine = llvm::EngineBuilder(&m_llvmModule).setErrorStr(&m_engineErrStr).create();
    //
    // Initialize optimization passes
    //
    // PassManager to optimize the whole module
    m_passManager->add(llvm::createFunctionInliningPass());

    // Function pass manager
    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    m_funcPassManager->add(new llvm::DataLayout(*m_engine->getDataLayout()));
    // Promote allocas to registers.
    m_funcPassManager->add(llvm::createPromoteMemoryToRegisterPass());
    // Provide basic AliasAnalysis support for GVN.
    m_funcPassManager->add(llvm::createBasicAliasAnalysisPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    m_funcPassManager->add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    m_funcPassManager->add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    m_funcPassManager->add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    m_funcPassManager->add(llvm::createCFGSimplificationPass());

    m_funcPassManager->add(llvm::createLoopUnrollPass());
    m_funcPassManager->add(llvm::createLoopInstSimplifyPass());
    m_funcPassManager->add(llvm::createLoopRotatePass());
    m_funcPassManager->add(llvm::createLoopIdiomPass());
    m_funcPassManager->add(llvm::createLoopVectorizePass ());
    m_funcPassManager->doInitialization();
}

// Destructor
ComputeEngine::~ComputeEngine()
{
    delete m_builder;
    delete m_funcPassManager;
    delete m_passManager;
    delete m_engine;
}

Status ComputeEngine::run(Node &node, const Context &context)
{
    std::cout << "Compute" << std::endl;
    // List function in the current module
    // TODO : might go in LlvmUtils ??
    //llvm::Module::FunctionListType &flist = m_llvmModule.getFunctionList();
    //llvm::Module::FunctionListType::iterator it;
    //for (it = flist.begin(); it != flist.end(); ++it) {
    //    std::cout << (*it).getName().str() << std::endl;
    //}

    // Build execution graph recursively
    llvm::Value *cc = buildCallGraph(Output0(node), context);
    std::cout << "result of callgraph = " << cc << std::endl;

    Function* LF = m_engine->FindFunctionNamed("ComputeEngine::runonce");

    m_llvmModule.dump();
    m_passManager->run(m_llvmModule);
    std::cerr << "=========================================" << std::endl;
    m_llvmModule.dump();
    m_funcPassManager->run(*LF);


    //LF->dump();
    // Compile the function and returns a pointer to it
    void *FPtr = m_engine->getPointerToFunction(LF);
    double (*FP)() = (double (*)())(intptr_t)FPtr;

    // Execute the function
    std::cout << "result=" << FP() << std::endl;


    // Remove the function from the module
#if USE_CONSTANT
    LF->eraseFromParent();
#endif
    return SUCCESS;
}

