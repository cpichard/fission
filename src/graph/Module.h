#ifndef MODULE_H
#define MODULE_H

#include <list>
#include "Node.h"

/// A module inherits a node, so it has inputs, outputs and parameters.
/// It can register new types of nodes and be able to create those. 
/// A module handle the dataflow inside all is child nodes.
/// All nodes are owned by a node or a module, the module being the last parent of the hierarchy
class Module : public Node
{
    // TODO : remove
    friend class ModuleTest;

public:
    Module(const std::string &name)
    : Node(name, 0, NULL){}
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

private:
    
    /// Types of node known by this module
    std::list<NodeDesc*>    m_nodeDesc;
    
    /// Dataflow inside the module 
    Graph<Plug, PlugLink>           m_dataFlowGraph;
};


#endif//MODULE_H
