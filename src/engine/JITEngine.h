#ifndef JITENGINE_H
#define JITENGINE_H

#include <string>
#include <llvm/IR/IRBuilder.h>

// Forward declarations
namespace llvm {
    class ExecutionEngine;
    class Module;
    class PassManager;
    class FunctionPassManager;
    class Value;
    class Function;
};

namespace fission {

// Forward declarations
class Context;
class NodeDesc;
class NodeCompiler;
class Plug;

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
    //llvm::Value * mapContext(const Context &context);

    llvm::IRBuilder<>   *irBuilder(){return m_irBuilder;}

    template<typename ValueType>
    llvm::Value * mapValue(const ValueType *);

    template<typename ValueType>
    llvm::Value * mapValueAsConstant(const ValueType &);

    void optimizeFunction(llvm::Function &f);

    /// 
    void optimizeModule();
    
    /// jit compile and run functionName
    void runFunctionNamed(const char *functionName);

    /// Clean code associated to the function
    void freeFunctionNamed(const char *functionName);

    /// Return the jit llvm module
    llvm::Module & getModule();

private:
    //NodeCompiler                *m_nodeCompiler;
    llvm::Module                *m_llvmModule;
    llvm::PassManager           *m_llvmPassManager;
    llvm::FunctionPassManager   *m_llvmFuncPassManager;
    llvm::ExecutionEngine       *m_llvmEngine;
    std::string                 m_eeerror;
    llvm::IRBuilder<>           *m_irBuilder;
};

};//namespace fission

#endif//JITENGINE_H
