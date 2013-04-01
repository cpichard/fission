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

#define DEBUG_ARG_PASSING 0

// Constructor
ComputeEngine::ComputeEngine(Module &fissionModule, JITEngine &jit)
: m_module(fissionModule)
, m_jit(&jit){}

// Destructor
ComputeEngine::~ComputeEngine() {
}

/// Recursively build the call graph from the node graph
llvm::Value *
ComputeEngine::buildCallGraphRecursively(
      Plug *plug
    , llvm::Value *context)
{
    llvm::Module &module = m_jit->getModule();
    llvm::IRBuilder<> &builder = *m_jit->irBuilder();
    if(IsOutput(plug)) {
        // iterate on args,
        // Look up the name in the global module table.
        std::string Callee(std::string(TypeName(Owner(plug))) + "_execute");
        llvm::Function *CalleeF = module.getFunction(Callee);
        if (CalleeF == 0) {
            std::cout << "ERROR Function " << Callee << " not found" << std::endl;
            m_jit->getModule().dump();
            exit(0);
        } else {
            std::cout << "Function " << Callee << " found" << std::endl;
        }

        // TODO :Optimize function
        // check clang -O3 passes
        // m_funcPassManager->run(*CalleeF);
        m_jit->optimizeFunction(*CalleeF);

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

        // DEBUG nb of arguments and types of arguments
#if DEBUG_ARG_PASSING
        std::cout << "Create call " << Name(Owner(plug)) << "_tmp, arguments are :" << std::endl;
        llvm::Function::ArgumentListType &al = CalleeF->getArgumentList();
        llvm::Function::ArgumentListType::iterator ait = al.begin();
        for (; ait!=al.end(); ++ait) {
            ait->dump();
        }
        std::cout << "  built arguments: " << std::endl;
        for(unsigned int i=0; i < nbArgs+1; i++) {
            ArgsV[i]->dump();
        }
#endif
        llvm::Value *ret=builder.CreateCall(CalleeF, ArgsV, Name(Owner(plug))+"_tmp");
        return ret;

    } else if(IsInput(plug)) {
        const size_t nbConnections = NbConnectedInputs(plug);
        if (nbConnections==0) {
            // recursive call
            // TODO : Create a dummy value
            // TODO : Create a NULL Value
            std::cout << "Error, nbConnections==0" << std::endl;
            assert(0); // shouldn't happen with the current setup
            return NULL;
        } else {
            // only one connection allowed
            assert(nbConnections==1);
            GraphIterator<Plug, PlugLink> n(plug);
            return buildCallGraphRecursively(n.nextVertex(), context);
        }

    } else if(IsParameter(plug)) {
        Parameter *param = static_cast<Parameter*>(plug);

        if( ValueTypeOf(param) == Type<Float>() ) {
            float tmp;
            param->evalFloat(tmp);
        // TODO return m_jit->mapValueToConstant(param->asFloat());
            return m_jit->mapValueAsConstant(tmp);
        } else if (ValueTypeOf(param) == Type<String>()) {
            std::string strtmp;
            param->evalString(strtmp);
            return m_jit->mapValue(strtmp.c_str());
        } else if (ValueTypeOf(param) == Type<Int>()) {
            int tmp;
            param->evalInt(tmp);
        // TODO return m_jit->mapValueToConstant(param->asInt());
            return m_jit->mapValueAsConstant(tmp);

        } else {
            assert(0 && "Type mapping not implemented");
        }
    } else {
        // ERROR !!
        assert(0 && "Invalid plug type");
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
            &m_jit->getModule());

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    m_jit->irBuilder()->SetInsertPoint(BB);
    llvm::Value *ctxVal = m_jit->mapValueAsConstant(context);

    m_jit->irBuilder()->CreateRet(buildCallGraphRecursively(plug, ctxVal));
    llvm::verifyFunction(*F);
    return 0;
}


Status ComputeEngine::run(Node &node, const Context &context)
{
    std::cout << "Compute" << std::endl;

    // Prepare compute data
    //buildComputeData()

    // Build execution graph recursively
    llvm::Value *cc = buildCallGraph(Output(node), context);
    std::cout << "result of callgraph = " << cc << std::endl;



    // Compile and run the newly created function
    m_jit->runFunctionNamed("ComputeEngine::runonce");
    m_jit->freeFunctionNamed("ComputeEngine::runonce");


    return SUCCESS;
}

