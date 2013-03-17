#include "engine/NodeCompiler.h"

#include <iostream>

#include <llvm/ADT/STLExtras.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Linker.h>
#include <llvm/Linker.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>

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
{}

NodeCompiler::~NodeCompiler()
{}

void NodeCompiler::compile(const char *fileName, llvm::Linker *llvmLinker)
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
        return; 

    // Emit only llvm code
    //llvm::OwningPtr<CodeGenAction> Act(new clang::EmitLLVMOnlyAction());
    clang::EmitLLVMOnlyAction *Act=new clang::EmitLLVMOnlyAction(&llvm::getGlobalContext());
    //Act->setLinkModule(llvmLinker->getModule());
    if (!Clang->ExecuteAction(*Act))
    {
        std::cout << "unable to link" << "\n";
    }

    //llvmLinker->getModule()->dump();
    std::cout << "====================" << "\n";
    llvm::Module *mod = Act->takeModule();
    delete Clang;
    delete Act;
    //llvmLinker->LinkInModule(Act->takeModule());
    std::string err2;
    //if( llvmLinker->LinkModules(llvmLinker->getModule(), mod, llvm::Linker::PreserveSource, &err2))
    if( llvmLinker->LinkModules(llvmLinker->getModule(), mod, llvm::Linker::DestroySource, &err2))
    {
        std::cout << "error linking module" << std::endl;
    }
    delete mod;
    std::cout << err2 << std::endl;
    // TODO : register node desc
    // Call a function that generates a new node ?
    //m_nodeDesc.push_back(newType);
    llvmLinker->getModule()->dump();
    //std::cout << Act->takeModule() << "\n";
}

};

