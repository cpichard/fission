#ifndef NODECOMPILER_H
#define NODECOMPILER_H

#include <vector>

// Forward declarations
namespace llvm {
    class ExecutionEngine;
    class Module;
};

namespace clang {

    class DiagnosticsEngine;
    class DiagnosticIDs;
    class DiagnosticOptions;
    class TextDiagnosticPrinter;
    class CompilerInstance;
    class EmitLLVMOnlyAction;
    namespace driver {
        class Driver;
    }
};

using clang::CompilerInstance;
using clang::DiagnosticIDs;
using clang::DiagnosticOptions;
using clang::DiagnosticsEngine;
using clang::driver::Driver;
using clang::TextDiagnosticPrinter;
using clang::EmitLLVMOnlyAction;

namespace fission {

    class NodeDesc;
    class JITEngine;

///
/// In charge of reading the node code and compile it
///
class NodeCompiler
{
public:
    NodeCompiler();
    ~NodeCompiler();

    llvm::Module *compile(const char *fileName);

private:
    // Compilation diagnostics
    DiagnosticOptions       *m_diagOpts;
    TextDiagnosticPrinter   *m_diagPrinter;
    DiagnosticIDs           *m_diagIDs;
    DiagnosticsEngine       *m_diagEngine;
    
    // Compiler
    Driver                  *m_driver;
    CompilerInstance        *m_clang;    
    EmitLLVMOnlyAction      *m_action;

    //
    std::vector<const char *>   m_args;
};

};//namespace fission

#endif//NODECOMPILER_H
