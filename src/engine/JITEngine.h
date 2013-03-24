#ifndef JITENGINE_H
#define JITENGINE_H

#include <string>


// Forward declarations
namespace llvm {
    class Linker;
    class ExecutionEngine;
    class Module;
    class PassManager;
    class FunctionPassManager;
    class Value;
};

namespace fission {

// Forward declarations
class Context;
class NodeDesc;
class NodeCompiler;

/// \brief JITEngine manage the just in time compilation
/// and code execution.
class JITEngine
{
public:
    JITEngine();
    ~JITEngine();

    /// Compile filename and return a new NodeDesc pointer
    NodeDesc * loadNodeDescription(const char *filename);

    /// Map a context value in memory or make it constant
    llvm::Value * mapContext(const Context &context);

    /// jit compile and run functionName
    void runFunctionNamed(const char *functionName);

    /// Return the jit llvm module
    llvm::Module & getModule();

private:
    NodeCompiler                *m_nodeCompiler;
    llvm::Module                *m_llvmModule;
    llvm::PassManager           *m_llvmPassManager;
    llvm::FunctionPassManager   *m_llvmFuncPassManager;
    llvm::Linker                *m_llvmLinker;
    llvm::ExecutionEngine       *m_llvmEngine;
    std::string                 m_eeerror;
};

};//namespace fission

#endif//JITENGINE_H
