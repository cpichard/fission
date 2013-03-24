#include <iostream>
#include "JITEngine.h"

#include "NodeCompiler.h"
#include "JITEngine.h"
#include "NodeDesc.h"
#include "Module.h"

#include <llvm/ADT/STLExtras.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Constants.h>
#include <llvm/DataLayout.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IRBuilder.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Linker.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/Scalar.h>



namespace fission {
JITEngine::JITEngine()
: m_llvmModule(0)
, m_llvmPassManager(0)
, m_llvmFuncPassManager(0)
, m_llvmLinker(0)
, m_llvmEngine(0)
, m_eeerror("")
{
    // Init llvm target
    llvm::InitializeNativeTarget();
    llvm::LLVMContext &llvmContext = llvm::getGlobalContext();
    m_llvmLinker = new llvm::Linker("ModuleLinker", "JITEngine", llvmContext, 0);

    m_llvmModule = new llvm::Module("JIT", llvmContext);

    // Create a Execution engine via the engine builder
    llvm::EngineBuilder engineBuilder(m_llvmModule);
    engineBuilder.setUseMCJIT(true); // Test gdb, I suppose it will create an instance of MCJIT instead of JIT
    //engineBuilder.setOptLevel(0); // Test gdb
    engineBuilder.setErrorStr(&m_eeerror);
    engineBuilder.setAllocateGVsWithCode(true); // Global values
    m_llvmEngine = engineBuilder.create();

    m_llvmPassManager = new llvm::PassManager();
    m_llvmPassManager->add(llvm::createFunctionInliningPass());

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

    m_llvmFuncPassManager->add(llvm::createLoopUnrollPass());
    m_llvmFuncPassManager->add(llvm::createLoopInstSimplifyPass());
    m_llvmFuncPassManager->add(llvm::createLoopRotatePass());
    m_llvmFuncPassManager->add(llvm::createLoopIdiomPass());
    m_llvmFuncPassManager->add(llvm::createLoopVectorizePass ());
    m_llvmFuncPassManager->doInitialization();
}



JITEngine::~JITEngine()
{
    // TODO : release execution engine
    //delete m_llvmEngine;
    delete m_llvmFuncPassManager;
    delete m_llvmPassManager;
    delete m_llvmLinker;
    delete m_llvmModule;
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
    std::string err2;
    llvm::Module::FunctionListType &flist = nodeModule->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    std::string createInstanceFunc;
    for(;it!=flist.end();++it) {
        if(it->getName().find("getInstance")!=std::string::npos) {
            std::cout << it->getName().data() <<"\n";
            createInstanceFunc=it->getName().data();
        }
    }

    /// Link the new module in the current one
    if( m_llvmLinker->LinkModules(&getModule(), nodeModule, llvm::Linker::DestroySource, &err2)) {
        std::cout << "error linking module" << std::endl;
    }
    delete nodeModule;

    m_llvmPassManager->run(getModule());
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

llvm::Value *
JITEngine::mapContext(const Context &context)
{
    // Make a constant from the context stored in a global variable
    llvm::StructType *ctxType = getModule().getTypeByName ("class.fission::Context");
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
    llvm::GlobalVariable *glob = new llvm::GlobalVariable( *m_llvmModule
                                , ctxType
                                , true
                                , llvm::GlobalValue::InternalLinkage
                                , res);
#else
    // Use external variable
    llvm::GlobalVariable *glob = new llvm::GlobalVariable( *m_llvmModule
                                , ctxType
                                , false // is constant
                                , llvm::GlobalValue::ExternalLinkage
                                , NULL);
    m_llvmEngine->addGlobalMapping(glob, (void *)&context);
#endif
    return glob;
}


void JITEngine::runFunctionNamed(const char *functionName)
{
    llvm::Function* LF = m_llvmEngine->FindFunctionNamed(functionName);

    //getModule().dump();
    m_llvmPassManager->run(getModule());
    // DEBUG PRRINT
    //std::cerr << "=========================================" << std::endl;
    //getModule().dump();
    m_llvmFuncPassManager->run(*LF);


    //LF->dump();
    // Compile the function and returns a pointer to it
    void *FPtr = m_llvmEngine->getPointerToFunction(LF);
    double (*FP)() = (double (*)())(intptr_t)FPtr;

    // Execute the function
    std::cout << "result=" << FP() << std::endl;


    // Remove the function from the module
#if USE_CONSTANT
    LF->eraseFromParent();
#endif
}


};//namespace fission
