#include "NodeCollection.h"
#include "TestValue.h" // TODO remove

Node * NodeCollection::createNode(const std::string &nodeTypeName, const std::string &nodeName)
{
    if(nodeTypeName.compare("TestValue")==0)
    {
        size_t id = m_nodes.size(); // Hope we don't count the number of values
        Node *node = new Node(nodeName, id, new TestValue()); 
        m_nodes.push_back(node);
        return node;
    }
    return NULL;
}

void NodeCollection::disposeNode(Node *node)
{}

void NodeCollection::registerNodeType(NodeType *newType)
{
    // TODO : basic sanity check
    m_nodeTypes.push_back(newType);
}

void NodeCollection::unregisterNodeType(NodeType *type)
{
    m_nodeTypes.remove(type);
}

