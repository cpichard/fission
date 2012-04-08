#include <NodeGraph.h>
#include <TestValue.h>
#include <iostream>
NodeGraph::NodeGraph(const std::string &name)
: Node(name)
, m_lastIndex(0)
{
    m_nodes.reserve(100);    
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
    m_lastIndex++;
    m_nodes[m_lastIndex] = node;
    node->m_owner = this;
    node->m_id = m_lastIndex;
    
    return *node; 
}


