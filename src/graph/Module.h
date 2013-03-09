#ifndef MODULE_H
#define MODULE_H

#include <list>
#include "Node.h"

namespace llvm {
class Linker;
};

// TODO : remove moduletest, it's just for ... tests
class ModuleTest;

namespace fission {

class ComputeEngine;
/// A module is a container and factory of nodes.
/// It inherits properties of a node : inputs, outputs and parameters.
/// It can register new types of nodes and be able to create those.
/// A module handle the dataflow inside all is child nodes.
/// All nodes are owned by a node or a module, the module being the last parent of the hierarchy
class Module : public Node
{
    // TODO : remove, this is only for testing
    friend class ::ModuleTest;
    friend class fission::ComputeEngine;

public:
    /// Constructor
    Module(const std::string &name);

    /// Destructor
    ~Module();

    /// Creates a node ...
    Node * createNode(const std::string &nodeName, const std::string &nodeTypeName);

    /// Get rid of a node
    void disposeNode(Node *node);

    // A module can register new types of node and be able to generate them
    void registerNodeDesc(NodeDesc *newType);
    void unregisterNodeDesc(NodeDesc *type);

    // connect two plugs
    void connect(Plug *src, Plug *dst);

//private:

    /// Types of node known by this module
    std::list<NodeDesc*>    m_nodeDesc;

    /// Dataflow inside the module
    Graph<Plug, PlugLink>   m_dataFlowGraph;

    /// llvm module that contains the generated code and functions
    llvm::Linker            *m_llvmLinker;

};

}; // namespace fission
#endif//MODULE_H
