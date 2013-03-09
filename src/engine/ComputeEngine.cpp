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


llvm::Value *recursiveAst(
      Plug *plug
    , Graph<Plug, PlugLink> &graph
    , llvm::Module &module
    , llvm::IRBuilder<> &builder
    , const Context &context)
{
    if(IsOutput(plug)) {
        // iterate on args,
        // Look up the name in the global module table.
        std::string Callee(std::string(TypeName(Owner(plug))) + "::execute");
        llvm::Function *CalleeF = module.getFunction(Callee);
        if (CalleeF == 0) {
            std::cout << "ERROR Function " << Callee << " not found" << std::endl;
            return NULL;
        }

        std::cout << "====Fun: \n";
        CalleeF->getFunctionType()->getParamType(0)->dump() ;
        std::cout << "====\n";

        const size_t nbArgs = NbConnectedInputs(plug);
        std::vector<llvm::Value*> ArgsV(nbArgs+1);
        TraversalStackElement<Plug, PlugLink> it(plug);

        // Make a constant from the context stored in a global variable
        llvm::StructType *ctxType = module.getTypeByName ("class.fission::Context");
        //llvm::PointerType *const ctxTypePtr = llvm::PointerType::getUnqual( ctxType );
        if(ctxType==0) {
            std::cout << "Context type not found" << std::endl;
            exit(0);
        }
        llvm::Constant *res = llvm::ConstantStruct::get(ctxType
                        , builder.getInt32(context.m_first)
                        , builder.getInt32(context.m_last)
                        , NULL );
        llvm::GlobalVariable *ga = new llvm::GlobalVariable( module
                                    , ctxType
                                    , true
                                    , llvm::GlobalValue::InternalLinkage
                                    , res);
        ArgsV[0] = ga;

        for (unsigned int i=1; i < nbArgs+1; ++i, ++it) {
            ArgsV[i] = recursiveAst(it.nextVertex(), graph, module, builder, context);
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
            TraversalStackElement<Plug, PlugLink> n(plug);
            return recursiveAst(n.nextVertex(), graph, module, builder, context);
        }

    } else {
        // ERROR !!
        return NULL;
    }
}


/// Build and ast starting at plug
llvm::Value *buildCallGraph(
      llvm::Module &module
    , Graph<Plug, PlugLink>  &graph
    , Plug *plug
    , const Context &context)
{
    llvm::IRBuilder<> builder(llvm::getGlobalContext());
    std::string funcName("ComputeEngine::run");
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
            &module);

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    builder.SetInsertPoint(BB);
    builder.CreateRet(recursiveAst(plug, graph, module, builder, context));
    llvm::verifyFunction(*F);
    return 0;
}

// Constructor
ComputeEngine::ComputeEngine()
{
}

// Destructor
ComputeEngine::~ComputeEngine()
{}

Status ComputeEngine::compute(Module &module, Node &node, const Context &context)
{
    std::cout << "Compute" << std::endl;
    llvm::Module &llvmMod = *module.m_llvmLinker->getModule();

    llvm::Module::FunctionListType &flist = llvmMod.getFunctionList();
    llvm::Module::FunctionListType::iterator it;
    for (it = flist.begin(); it != flist.end(); ++it) {
        std::cout << (*it).getName().str() << std::endl;
    }

    // Build execution graph recursively
    llvm::Value *cc = buildCallGraph(llvmMod, module.m_dataFlowGraph, Input0(node), context);
    std::cout << "cc = " << cc << std::endl;

    std::string ErrStr;
    llvm::ExecutionEngine *ee = llvm::EngineBuilder(&llvmMod).setErrorStr(&ErrStr).create();

    Function* LF = ee->FindFunctionNamed("ComputeEngine::run");

    llvm::PassManager optPM;
    //optPM.add(new llvm::TargetData(&llvmMod));
    optPM.add(llvm::createFunctionInliningPass());
    optPM.run(llvmMod);
    // NOTE CYWILL : these optimizations work only on functions.
    // User PassManager to optimize globally
    // Function pass manager Run
    llvm::FunctionPassManager OurFPM(&llvmMod);
    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    OurFPM.add(new llvm::DataLayout(*ee->getDataLayout()));
    // Promote allocas to registers.
    OurFPM.add(llvm::createPromoteMemoryToRegisterPass());
    // Provide basic AliasAnalysis support for GVN.
    OurFPM.add(llvm::createBasicAliasAnalysisPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    OurFPM.add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    OurFPM.add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    OurFPM.add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    OurFPM.add(llvm::createCFGSimplificationPass());

    OurFPM.add(llvm::createLoopUnrollPass());

    OurFPM.doInitialization();
    OurFPM.run(*LF);

    llvmMod.dump();
    LF->dump();
    // Compile the function and returns a pointer to it
    void *FPtr = ee->getPointerToFunction(LF);
    double (*FP)() = (double (*)())(intptr_t)FPtr;

    std::cout << "result=" << FP() << std::endl;

    // Execute the function on node
    return SUCCESS;
}

