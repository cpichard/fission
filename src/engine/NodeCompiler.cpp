#include "engine/NodeCompiler.h"
#include "graph/Name.h"
#include "graph/NodeDesc.h"

#include <iostream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Host.h>

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
using clang::EmitLLVMOnlyAction;
using llvm::sys::getDefaultTargetTriple;

namespace fission {

NodeCompiler::NodeCompiler()
: m_diagOpts(new DiagnosticOptions())
, m_diagPrinter(new TextDiagnosticPrinter(llvm::errs(), m_diagOpts))
, m_diagIDs(new DiagnosticIDs)
, m_diagEngine(new DiagnosticsEngine(m_diagIDs, m_diagOpts, m_diagPrinter))
, m_driver(new Driver("clang", getDefaultTargetTriple(), "a.out", *m_diagEngine))
, m_clang(new CompilerInstance())
, m_action(new EmitLLVMOnlyAction(&llvm::getGlobalContext()))
, m_args()
{
    m_driver->UseStdLib = true;
    m_driver->CCCIsCXX = true;
    //m_driver->CCCIsCPP = true;

    // TODO : no path in code !!!
    // it is needed for standard headers like stddef.h
    m_driver->ResourceDir = CLANG_RESSOURCEDIR;

    m_args.push_back("-xc++");
    m_args.push_back("-I" SRC_DIR);

}

NodeCompiler::~NodeCompiler()
{
    //delete m_action;
    delete m_clang;
    delete m_driver;
    delete m_diagEngine;
    // Is it deleted by the engine ?
    //delete m_diagIDs;
    //delete m_diagPrinter;
    //delete m_diagOpts;
}

llvm::Module *NodeCompiler::compile(const char *fileName)
{
    // Add filename as the last argument of the compiler
    char globfilename[512];
    strcpy(globfilename, SRC_DIR"/");
    strcat(globfilename, fileName);
    m_args.push_back(globfilename);
    const llvm::OwningPtr<Compilation>
        Compilation(
            m_driver->BuildCompilation(llvm::makeArrayRef(m_args)));

    // Compilation Job to get the correct arguments
    const JobList &Jobs = Compilation->getJobs();
    const Command *Cmd = llvm::cast<Command>(*Jobs.begin());
    const ArgStringList *const CC1Args = &Cmd->getArguments();

    //DEBUG Driver->PrintActions(*Compilation);

    llvm::OwningPtr<CompilerInvocation>
                    CI(new CompilerInvocation);
    CompilerInvocation::CreateFromArgs(
        *CI, CC1Args->data() + 1, CC1Args->data() + CC1Args->size(), *m_diagEngine);

    // Create the compiler instance
    m_clang->setInvocation(CI.take());

    // Diagnostics
    m_clang->createDiagnostics();
    m_args.pop_back(); // Remove filename for future compilation
    if (!m_clang->hasDiagnostics())
        return NULL;

    // Emit only llvm code
    llvm::OwningPtr<CodeGenAction> action(m_action);
    llvm::Module *mod=NULL;
    if (!m_clang->ExecuteAction(*action)) {
        std::cout << "unable to generate llvm code" << "\n";
    } else {
        mod = action->takeModule();
    }

    return mod;
}

};

