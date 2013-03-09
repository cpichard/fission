#ifndef COMPUTEENGINE_H
#define COMPUTEENGINE_H

#include <list>
#include "Module.h"
#include "Node.h"
#include "Status.h"
#include "Context.h"

// Forward llvm declarations
namespace llvm {
class PassManager;
class FunctionPassManager;
class ExecutionEngine;
class Module;
class Value;
};

#include <llvm/IRBuilder.h>

namespace fission {

class ComputeEngine
{
public:
    ComputeEngine(Module &);
    ~ComputeEngine();

    Status run(Node &, const Context &);

private:
    Module  &m_module;

    // LLVM Stuff
    llvm::Module                &m_llvmModule;
    llvm::PassManager           *m_passManager;
    llvm::FunctionPassManager   *m_funcPassManager;
    llvm::ExecutionEngine       *m_engine;
    std::string                 m_engineErrStr;
    llvm::IRBuilder<>           *m_builder;

    // Function to build the call graph from the node graph
    llvm::Value *buildCallGraph( Plug *plug, const Context &context);
    llvm::Value *buildCallGraphRecursively(Plug *plug, llvm::Value *context);
    llvm::Value *buildContext(const Context &);
    // std::list<Task*>
    // CacheManager
    // EventManager
    // Scheduler, etc...
};
}; // namespace fission
#endif//COMPUTEENGINE_H
