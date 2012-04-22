#include "Module.h"
#include "TestValue.h" // TODO remove
#include "Name.h"
#include "Types.h"

/// Destructor
/// Module is supposed to destroy everything that it owns
Module::~Module() {

    /// Delete node descriptions
    /// Destroy Plugs
    /// Destroy PlugLinks
    /// Destroy Nodes
}



/// Creates a node from a known type
Node * Module::createNode(const std::string &nodeTypeName, const std::string &nodeName)
{
    std::list<NodeDesc*>::iterator it;
    for (it=m_nodeDesc.begin(); it != m_nodeDesc.end(); ++it) {
        
        // Type name comparison. There surely is a better way of testing types
        if (nodeTypeName.compare(TypeName(*it))==0) {

            // Last Id is equal to the size of the vector
            size_t id = m_nodes.size(); // Hope vector doesn't count the number of values
            Node *node = new Node(nodeName, id, *it); 
            // TODO : node.m_owner = 
            //node.m_module = this;
            m_nodes.push_back(node);

            // Add all the plugs of this new node to the graph
            const size_t nbInputs = NbInputs(node);
            for (size_t i=0; i<nbInputs; i++) {
                m_dataFlowGraph.addVertex(node->input(i));  
            }

            const size_t nbOutputs = NbOutputs(node);
            for (size_t j=0; j<nbOutputs; j++) {

                // Add vertex
                m_dataFlowGraph.addVertex(node->output(j));
            
                // Connect all imputs to current outputs
                for (size_t i=0; i<nbInputs; i++) {
                    // TODO !!! 
                    PlugLink *pl = new PlugLink("",0, NULL);
                    pl->m_src = node->input(i);
                    pl->m_dst = node->output(j);
                    m_dataFlowGraph.addEdge(pl);  
                }
            }
             
            // TODO : is it useful to return the node ?
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
    m_nodeDesc.push_back(newType);
}

void Module::unregisterNodeDesc(NodeDesc *type) {
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
    PlugLink *pl = new PlugLink("",0, NULL);
    pl->m_src = src;
    pl->m_dst = dst;
    m_dataFlowGraph.addEdge(pl);  
    
    // TODO 
    // Test for cycles


}
