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

//

namespace fission {

class JITEngine;

class ComputeEngine
{
public:
    ComputeEngine(JITEngine &jite);
    ~ComputeEngine();

    Status run(Node &, const Context &);

private:
    // llvm jit stuff
    JITEngine                   *m_jit;
    //llvm::IRBuilder<>           *m_builder;

    // craft

    // Function to build the call graph from the node graph
    llvm::Value *buildCallGraph(Plug *plug, const Context &context);
    llvm::Value *buildCallGraphRecursively(Plug *plug, llvm::Value *context);
};
}; // namespace fission
#endif//COMPUTEENGINE_H
