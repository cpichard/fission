#include "NodeCollection.h"
#include "TestValue.h" // TODO remove
#include "Name.h"
#include "Types.h"

//
Node * NodeCollection::createNode(const std::string &nodeTypeName, const std::string &nodeName)
{
    std::list<NodeType*>::iterator it;
    for(it=m_nodeTypes.begin(); it != m_nodeTypes.end(); ++it)
    {
        if(nodeTypeName.compare(TypeName(*it))==0)
        {
            size_t id = m_nodes.size(); // Hope we don't count the number of values
            Node *node = new Node(nodeName, id, *it); 
            m_nodes.push_back(node);
            return node;
        }
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

