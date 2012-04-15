#include <NodeGraph.h>
#include <TestValue.h>
#include <iostream>


NodeGraph::NodeGraph(const std::string &name)
: Node(name)
, m_lastNodeIndex(0)
, m_lastLinkIndex(0)
{
    m_nodes.reserve(100);    
    m_links.reserve(100);    
}

NodeGraph::~NodeGraph()
{}


Node &NodeGraph::createNode(const std::string &nodeType, const std::string &nodeName)
{
    // Create a dummy node if the type isn't found
    Node *node=NULL;
    if(nodeType=="TestValue")
    {
        node = new TestValue(nodeName);    
    }
    else
    {
        node = new Node(nodeName);    
    }
    m_lastNodeIndex++;
    m_nodes[m_lastNodeIndex] = node;
    node->m_owner = this;
    node->m_id = m_lastNodeIndex;
    
    return *node; 
}

LinkId NodeGraph::connect( Plug &src, Plug &dst /*Connection type*/)
{
    // Create a new link
        
}







