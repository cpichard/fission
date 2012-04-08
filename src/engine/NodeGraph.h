#ifndef NODEGRAPH_H
#define NODEGRAPH_H

// A node graph contains a list of connected nodes
// and knows how to create and remove them
// Different node graph can be connected ??

#include <Node.h>
#include <utility>

class NodeGraph : public Node
{
public: 
    NodeGraph(const std::string &name);
    ~NodeGraph();
    
    // Node factory
    Node & createNode(const std::string &nodeType, const std::string &nodeName);
    // bool disposeNode (NodeId id){}

    LinkId connect( PlugId src, PlugId dst /*Connection type*/);
    bool disconnect(LinkId);

    // List of the node is in GraphVertex
    // m_owned

    //typedef Plug* ConnectionType;
    //typedef Node* ParentingType;
private:
    std::vector<Node*>                      m_nodes; // ie m_owned
    std::vector< std::pair<PlugId,PlugId> >  m_links;
    int m_lastIndex;
};
#endif//NODEGRAPH_H
