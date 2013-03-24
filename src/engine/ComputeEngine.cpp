#include <iostream>
#include "ComputeEngine.h"
#include "GraphAlgorithms.h"
#include "Name.h"
#include "Plug.h"
#include "Edge.h"
#include "Context.h"
#include "JITEngine.h"

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

/// Recursively build the call graph from the node graph
llvm::Value *
ComputeEngine::buildCallGraphRecursively(
      Plug *plug
    , llvm::Value *context)
{
    llvm::Module &module = m_engine->getModule();
    llvm::IRBuilder<> &builder = *m_builder;
    if(IsOutput(plug)) {
        // iterate on args,
        // Look up the name in the global module table.
        std::string Callee(std::string(TypeName(Owner(plug))) + "_execute");
        llvm::Function *CalleeF = module.getFunction(Callee);
        if (CalleeF == 0) {
            m_engine->getModule().dump();
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
            // Create a NULL Value
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
            &m_engine->getModule());

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    m_builder->SetInsertPoint(BB);
    llvm::Value *ctxVal = m_engine->mapContext(context);

    m_builder->CreateRet(buildCallGraphRecursively(plug, ctxVal));
    llvm::verifyFunction(*F);
    return 0;
}

// Constructor
ComputeEngine::ComputeEngine(Module &fissionModule, JITEngine &jite)
: m_module(fissionModule)
, m_engine(&jite)
, m_builder(0)
{
    m_builder = new llvm::IRBuilder<>(llvm::getGlobalContext());
}


// Destructor
ComputeEngine::~ComputeEngine()
{
    delete m_builder;
}

Status ComputeEngine::run(Node &node, const Context &context)
{
    std::cout << "Compute" << std::endl;
    // List function in the current module
    // TODO : might go in LlvmUtils ??
    //llvm::Module::FunctionListType &flist = m_engine->getModule().getFunctionList();
    //llvm::Module::FunctionListType::iterator it;
    //for (it = flist.begin(); it != flist.end(); ++it) {
    //    std::cout << (*it).getName().str() << std::endl;
    //}

    // Build execution graph recursively
    llvm::Value *cc = buildCallGraph(Output0(node), context);
    std::cout << "result of callgraph = " << cc << std::endl;

    m_engine->runFunctionNamed("ComputeEngine::runonce");
    return SUCCESS;
}

