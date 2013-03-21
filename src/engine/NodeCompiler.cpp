#include "engine/NodeCompiler.h"
#include "graph/Name.h"
#include "graph/NodeDesc.h"

#include <iostream>

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

#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Tool.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Tooling/ArgumentsAdjusters.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>

using clang::CodeGenAction;
using clang::CompilerInstance;
using clang::CompilerInvocation;
using clang::DiagnosticIDs;
using clang::DiagnosticOptions;
using clang::DiagnosticsEngine;
using clang::driver::ArgStringList;
using clang::driver::Command;
using clang::driver::Compilation;
using clang::driver::Driver;
using clang::driver::JobList;
using clang::TextDiagnosticPrinter;
using llvm::sys::getDefaultTargetTriple;

namespace fission {

NodeCompiler::NodeCompiler()
: m_engine(0)
{}

NodeCompiler::~NodeCompiler()
{}

NodeDesc *NodeCompiler::compile(const char *fileName, llvm::Linker *llvmLinker)
{
    //
    std::cout << "Compiling " << fileName << "\n";

    // Diagnostics
    DiagnosticOptions *diagOpts = new DiagnosticOptions();
    TextDiagnosticPrinter *diagPrinter = new TextDiagnosticPrinter(llvm::errs(), diagOpts);
   // DiagnosticIDs *diagIDs = new DiagnosticIDs();
    llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> diagIDs(new clang::DiagnosticIDs);
    DiagnosticsEngine Diags(diagIDs, diagOpts, diagPrinter);

    // Driver that contains all clang options like header path, etc.
    Driver drv("clang", getDefaultTargetTriple()
                    , "a.out"
                    , false
                    , Diags);

    drv.UseStdLib = true;
    drv.CCCIsCXX = true;
    //drv->CCCIsCPP = true;
    // TODO : no path in code !!!
    // it is needed for standard headers like stddef.h
    drv.ResourceDir = "/home/cyril/usr/local/lib/clang/3.2";

    //// Create the compiler invocation
    std::vector<const char *> args;
    args.push_back("-xc++");
    args.push_back("-I/home/cyril/Develop/fission/src");
    args.push_back(fileName);
    const llvm::OwningPtr<Compilation>
        Compilation(
            drv.BuildCompilation(llvm::makeArrayRef(args)));

    // Compilation Job to get the correct arguments
    const JobList &Jobs = Compilation->getJobs();
    const Command *Cmd = llvm::cast<Command>(*Jobs.begin());
    const ArgStringList *const CC1Args = &Cmd->getArguments();

    //Driver->PrintActions(*Compilation);

    llvm::OwningPtr<CompilerInvocation>
                    CI(new CompilerInvocation);
    CompilerInvocation::CreateFromArgs(
        *CI, CC1Args->data() + 1, CC1Args->data() + CC1Args->size(), Diags);

    // Create the compiler instance
    CompilerInstance *Clang=new CompilerInstance();
    Clang->setInvocation(CI.take());

    // Diagnostics
    Clang->createDiagnostics(args.size(), &args[0]);
    if (!Clang->hasDiagnostics())
        return NULL;

    // Emit only llvm code
    //llvm::OwningPtr<CodeGenAction> Act(new clang::EmitLLVMOnlyAction());
    clang::EmitLLVMOnlyAction *Act=new clang::EmitLLVMOnlyAction(&llvm::getGlobalContext());
    //Act->setLinkModule(llvmLinker->getModule());
    if (!Clang->ExecuteAction(*Act)) {
        std::cout << "unable to link" << "\n";
    }

    //llvmLinker->getModule()->dump();
    std::cout << "====================" << "\n";
    llvm::Module *mod = Act->takeModule();
    delete Clang;
    delete Act;

    std::string err2;
    llvm::Module::FunctionListType &flist = mod->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    std::string createInstanceFunc;
    for(;it!=flist.end();++it) {
        if(it->getName().find("getInstance")!=std::string::npos) {
            std::cout << it->getName().data() <<"\n";
            createInstanceFunc=it->getName().data();
        }
    }

    if( llvmLinker->LinkModules(llvmLinker->getModule(), mod, llvm::Linker::PreserveSource, &err2)) {
        std::cout << "error linking module" << std::endl;
    }
    delete mod;
    llvm::EngineBuilder engineBuilder(llvmLinker->getModule());

    engineBuilder.setUseMCJIT(true); // Test gdb, I suppose it will create an instance of MCJIT instead of JIT

    //engineBuilder.setOptLevel(0); // Test gdb
    std::string engineError; // TODO remove if unused
    engineBuilder.setErrorStr(&engineError);
    engineBuilder.setAllocateGVsWithCode(true);
    //engine = llvm::EngineBuilder(llvmLinker->getModule()).create();
    m_engine = engineBuilder.create();
    m_engine->runStaticConstructorsDestructors(false); // Will allocate the static values

    // Find function that create an instance of the particular type
    // by convention this is getInstance
    llvm::Function* LF = m_engine->FindFunctionNamed(createInstanceFunc.c_str());

    // Run a graph viewer
    //LF->viewCFG();

    void *FPtr = m_engine->getPointerToFunction(LF);

    NodeDesc * (*FP)() = (NodeDesc * (*)())(intptr_t)FPtr;
    NodeDesc *nodedesc = FP();

    return nodedesc;
}

};

