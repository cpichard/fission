#include <iostream>
#include "JITEngine.h"

#include "NodeCompiler.h"
#include "JITEngine.h"
#include "NodeDesc.h"
#include "Module.h"
#include "StandardTypes.h"
#include "Type.h"
#include "Context.h"

#include <llvm/ADT/STLExtras.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Linker.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/ManagedStatic.h>

using llvm::Linker;

namespace fission {
JITEngine::JITEngine()
: m_llvmModule(0)
, m_llvmPassManager(0)
, m_llvmFuncPassManager(0)
, m_llvmEngine(0)
, m_eeerror("")
, m_irBuilder(new llvm::IRBuilder<>(llvm::getGlobalContext()))
{
    // Init llvm target
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::LLVMContext &llvmContext = llvm::getGlobalContext();
    m_llvmModule = new llvm::Module("JIT", llvmContext);

    // Create a Execution engine via the engine builder
    llvm::EngineBuilder engineBuilder(m_llvmModule);
    engineBuilder.setUseMCJIT(true); 
    engineBuilder.setOptLevel(llvm::CodeGenOpt::Aggressive); // Test gdb
    engineBuilder.setErrorStr(&m_eeerror);
    engineBuilder.setAllocateGVsWithCode(true); // Global values
    m_llvmEngine = engineBuilder.create();

    m_llvmPassManager = new llvm::PassManager();
    m_llvmPassManager->add(new llvm::DataLayout(*m_llvmEngine->getDataLayout()));
    m_llvmPassManager->add(llvm::createCFGSimplificationPass());     // Merge & remove BBs
    m_llvmPassManager->add(llvm::createInstructionCombiningPass());  // Combine silly seq's
    m_llvmPassManager->add(llvm::createTailCallEliminationPass());   // Eliminate tail calls
    m_llvmPassManager->add(llvm::createCFGSimplificationPass());     // Merge & remove BBs
    m_llvmPassManager->add(llvm::createReassociatePass());           // Reassociate expressions
    m_llvmPassManager->add(llvm::createLoopRotatePass());            // Rotate Loop
    m_llvmPassManager->add(llvm::createLICMPass());                  // Hoist loop invariants
    m_llvmPassManager->add(llvm::createInstructionCombiningPass());
    m_llvmPassManager->add(llvm::createIndVarSimplifyPass());        // Canonicalize indvars
    m_llvmPassManager->add(llvm::createLoopIdiomPass());             // Recognize idioms like memset.
    m_llvmPassManager->add(llvm::createLoopDeletionPass());          // Delete dead loops
    m_llvmPassManager->add(llvm::createLoopVectorizePass());
    m_llvmPassManager->add(llvm::createFunctionInliningPass());
    m_llvmPassManager->add(llvm::createBBVectorizePass());
    m_llvmPassManager->add(llvm::createInstructionCombiningPass());
    
    // Function pass manager
    m_llvmFuncPassManager = new llvm::FunctionPassManager(m_llvmModule);
    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    m_llvmFuncPassManager->add(new llvm::DataLayout(*m_llvmEngine->getDataLayout()));
    // Promote allocas to registers.
    m_llvmFuncPassManager->add(llvm::createPromoteMemoryToRegisterPass());
    // Provide basic AliasAnalysis support for GVN.
    m_llvmFuncPassManager->add(llvm::createBasicAliasAnalysisPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    m_llvmFuncPassManager->add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    m_llvmFuncPassManager->add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    m_llvmFuncPassManager->add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    m_llvmFuncPassManager->add(llvm::createCFGSimplificationPass());

    // Unroll small loops
    m_llvmFuncPassManager->add(llvm::createLoopInstSimplifyPass());
    m_llvmFuncPassManager->add(llvm::createLoopRotatePass());
    // Recognize idioms like memset.
    m_llvmFuncPassManager->add(llvm::createLoopIdiomPass());
    m_llvmFuncPassManager->add(llvm::createLoopVectorizePass());
    m_llvmFuncPassManager->add(llvm::createLoopUnrollPass());
    m_llvmFuncPassManager->add(llvm::createBBVectorizePass());
    m_llvmFuncPassManager->doInitialization();
}

JITEngine::~JITEngine()
{
    delete m_irBuilder;
    m_llvmEngine->runStaticConstructorsDestructors(true);
    delete m_llvmEngine;
    // m_llvmModule should be deleted by the engine
    delete m_llvmFuncPassManager;
    delete m_llvmPassManager;
    llvm::llvm_shutdown();
}

void JITEngine::optimizeFunction(llvm::Function &f) {
    f.viewCFG();
    m_llvmFuncPassManager->run(f);
    f.viewCFG();
}

void JITEngine::optimizeModule() {
    m_llvmPassManager->run(*m_llvmModule);
}
NodeDesc * JITEngine::loadNodeDescription(const char *filename)
{
    NodeCompiler    nc;
    // TODO add nc.addIncludeDir();
    llvm::Module *nodeModule = nc.compile(filename);
    if (!nodeModule) {
        return NULL;
    }
    // Search for the function getInstance in all the functions of 
    // this module
    llvm::Module::FunctionListType &flist = nodeModule->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    std::string createInstanceFunc;
    for(;it!=flist.end();++it) {
        if(it->getName().find("getInstance")!=std::string::npos) {
            //std::cout << it->getName().data() <<"\n";
            createInstanceFunc=it->getName().data();
        }
    }

    /// Link the new module in the current one
    std::string err2;
    //llvm::LLVMContext &llvmContext = llvm::getGlobalContext();
    //Linker *llvmLinker = new Linker("jitengine", "newnode", llvmContext, 0);

    if(Linker::LinkModules(m_llvmModule, nodeModule, llvm::Linker::PreserveSource, &err2)) {
        std::cout << "error linking module" << std::endl;
    }
    //llvmLinker->releaseModule();

    delete nodeModule; nodeModule=NULL;
    //delete llvmLinker; llvmLinker=NULL;

    m_llvmPassManager->run(*m_llvmModule);
    m_llvmEngine->runStaticConstructorsDestructors(false); // Will allocate the static values
    llvm::Function* LF = m_llvmEngine->FindFunctionNamed(createInstanceFunc.c_str());

    // Run a graph viewer
    //LF->viewCFG();

    // Call the getInstance function
    void *FPtr = m_llvmEngine->getPointerToFunction(LF);
    NodeDesc * (*FP)() = (NodeDesc * (*)())(intptr_t)FPtr;
    NodeDesc *nodedesc = FP();

    return nodedesc;
}

llvm::Module & JITEngine::getModule()
{
    return *m_llvmModule;
}

template<>
llvm::Value *
JITEngine::mapValue(const Context *context)
{
    // Make a constant from the context stored in a global variable
    llvm::StructType *ctxType = m_llvmModule->getTypeByName ("class.fission::Context");
    // Note : get pointer type from a type
    if(ctxType==0) {
        std::cout << "Context type not found" << std::endl;
        exit(0);
    }

    llvm::GlobalVariable *glob = new llvm::GlobalVariable( *m_llvmModule
                                , ctxType
                                , false // is constant
                                , llvm::GlobalValue::ExternalLinkage
                                , NULL);
    m_llvmEngine->addGlobalMapping(glob, (void *)context);
    return glob;
}

template<>
llvm::Value *
JITEngine::mapValueAsConstant(const Context &context) {
    // Make a constant from the context stored in a global variable
    llvm::StructType *ctxType = m_llvmModule->getTypeByName ("class.fission::Context");
    // Note : get pointer type from a type
    //llvm::PointerType *const ctxTypePtr = llvm::PointerType::getUnqual( ctxType );
    if(ctxType==0) {
        std::cout << "Context type not found" << std::endl;
        exit(0);
    }
    llvm::Constant *res = llvm::ConstantStruct::get(ctxType
                    , m_irBuilder->getInt32(context.m_first)
                    , m_irBuilder->getInt32(context.m_last)
                    , NULL );
    llvm::GlobalVariable *glob = new llvm::GlobalVariable( *m_llvmModule
                                , ctxType
                                , true
                                , llvm::GlobalValue::InternalLinkage
                                , res);
    return glob;
}


template<>
llvm::Value * JITEngine::mapValue(const char *str) {

    return m_irBuilder->CreateGlobalStringPtr(str);
}

template<>
llvm::Value * JITEngine::mapValueAsConstant(const float &value)
{
    return llvm::ConstantFP::get(m_irBuilder->getFloatTy(), value);
}

template<>
llvm::Value * JITEngine::mapValueAsConstant(const int &value)
{
    return llvm::ConstantInt::get(m_irBuilder->getInt32Ty(), value);
}

void JITEngine::runFunctionNamed(const char *functionName)
{
    llvm::Function* LF = m_llvmEngine->FindFunctionNamed(functionName);

    //*m_llvmModule.dump();
    m_llvmPassManager->run(*m_llvmModule);
    // DEBUG PRRINT
    //std::cerr << "=========================================" << std::endl;
    //*m_llvmModule.dump();
    m_llvmFuncPassManager->run(*LF);

    LF->viewCFG();

    //LF->dump();
    // Compile the function and returns a pointer to it
    void *FPtr = m_llvmEngine->getPointerToFunction(LF);
    double (*FP)() = (double (*)())(intptr_t)FPtr;

    // Execute the function
    FP();
    //std::cout << "result=" << FP() << std::endl;
}

void JITEngine::freeFunctionNamed(const char *functionName) {

    llvm::Function* LF = m_llvmEngine->FindFunctionNamed(functionName);
    if (LF) {
        // Free ?
        m_llvmEngine->freeMachineCodeForFunction(LF);
        // Remove the function from the module
        LF->eraseFromParent();
    }
}

};//namespace fission
