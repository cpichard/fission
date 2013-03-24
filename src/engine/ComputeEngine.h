#ifndef COMPUTEENGINE_H
#define COMPUTEENGINE_H

#include <list>
#include "graph/Module.h"
#include "graph/Node.h"
#include "engine/Status.h"
#include "engine/Context.h"

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

class JITEngine;

class ComputeEngine
{
public:
    ComputeEngine(Module &, JITEngine &jite);
    ~ComputeEngine();

    Status run(Node &, const Context &);

private:
    /// Fission module the engine is using
    Module  &m_module;

    // llvm jit stuff
    JITEngine                   *m_engine;
    llvm::IRBuilder<>           *m_builder;

    // Function to build the call graph from the node graph
    llvm::Value *buildCallGraph( Plug *plug, const Context &context);
    llvm::Value *buildCallGraphRecursively(Plug *plug, llvm::Value *context);
};
}; // namespace fission
#endif//COMPUTEENGINE_H
