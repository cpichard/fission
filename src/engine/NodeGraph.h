#ifndef NODEGRAPH_H
#define NODEGRAPH_H

// A node graph contains a list of connected nodes
// and knows how to create and remove them
// Different node graph can be connected ??

#include <Node.h>
#include <Link.h>
#include <utility>

class NodeGraph : public Node
{
public: 
    NodeGraph(const std::string &name);
    ~NodeGraph();
    
    // Node factory
    Node & createNode(const std::string &nodeType, const std::string &nodeName);
    // bool disposeNode (NodeId id){}

    LinkId connect( Plug & src, Plug & dst /*Connection type*/);
    bool disconnect(LinkId);

    // List of the node is in GraphVertex
    // m_owned

private:
    std::vector<Node*>                      m_nodes; // ie m_owned in graph vertex
    std::vector<Link*>                      m_links;
    int m_lastNodeIndex;
    int m_lastLinkIndex;
        
    // TODO
    // Graph<Plug>                             m_dataFlowGraph;
};
#endif//NODEGRAPH_H
