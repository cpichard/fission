#include "Module.h"
#include "Name.h"
#include "Type.h"
#include "engine/NodeCompiler.h"

#include <iostream>

namespace fission {

using std::string;

Module::Module(const std::string &name)
: Node(name, NULL) 
{}


/// Destructor
/// Module is supposed to destroy everything that it owns
Module::~Module() {

    /// Destroy Plugs
    /// Destroy PlugLinks
    /// Destroy Nodes
    /// Delete node descriptions
}



/// Creates a node from a known type
Node * Module::createNode(const std::string &nodeTypeName, const std::string &nodeName)
{
    std::list<NodeDesc*>::iterator it;
    for (it=m_nodeDesc.begin(); it != m_nodeDesc.end(); ++it) {

        // Type name comparison. There surely is a better way of testing types
        if (nodeTypeName.compare(TypeName(*it))==0) {

            // Last Id is equal to the size of the vector
            Node *node = new Node(nodeName, *it);
            // TODO : node.m_owner =
            //node.m_module = this;
            m_nodes.push_back(node);

            // Add all the plugs of this new node to the graph
            const size_t nbInputs = NbInputs(node);
            for (size_t i=0; i<nbInputs; i++) {
                m_dataFlowGraph.addVertex(node->input(i));
            }

            // Add vertex
            m_dataFlowGraph.addVertex(node->output());

            // Connect all imputs to current outputs
            for (size_t i=0; i<nbInputs; i++) {
                // TODO !!!
                PlugLink *pl = new PlugLink("", NULL, node->input(i), node->output());
                m_dataFlowGraph.addEdge(pl);
            }

            const size_t nbParameters = NbParameters(node);
            for (size_t j=0; j<nbParameters; j++) {

                // Add vertex
                m_dataFlowGraph.addVertex(node->param(j));

                // Connect all imputs to current outputs
                PlugLink *pl = new PlugLink("", NULL, node->param(j), node->output());
                m_dataFlowGraph.addEdge(pl);
            }

            // TODO : is it useful to return the node ?
            // We should return and Id instead
            return node;
        }
    }
    return NULL;
}

/// Remove the node from the module ?? the graph ??
/// Actually deletes the node ?
void Module::disposeNode(Node *node) {

}

void Module::registerNodeDesc(NodeDesc *newType) {

    // Take ownership of this new type
    // TODO : check this type doesn't already exist
    m_nodeDesc.push_back(newType);
}
void Module::unregisterNodeDesc(NodeDesc *type) {

    // TODO : remove the execute function from llvm module

    // TODO: look if some nodes still uses this type
    m_nodeDesc.remove(type);
}

void Module::connect(Plug *src, Plug *dst) {

    // Double check we have the plugs here
    if (src==NULL || dst==NULL) {
        return;
    }

    // TODO : Look if this connection already exists
    if(m_dataFlowGraph.hasEdge(src, dst)) {
        return;
    }

    // Create a new pluglink
    // TODO : is it really useful to have a plug link struct ?
    PlugLink *pl = new PlugLink("", NULL, src, dst);
    m_dataFlowGraph.addEdge(pl);

    // TODO
    // Test for cycles


}

}; // namespace fission
