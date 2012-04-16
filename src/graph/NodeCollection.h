#ifndef NODECOLLECTION_H
#define NODECOLLECTION_H

#include <list>
#include "Node.h"

class NodeCollection : public Node
{
public:
    NodeCollection(const std::string &name)
    : Node(name, 0, NULL){}
    ~NodeCollection(){}

    Node * createNode(const std::string &nodeName, const std::string &nodeTypeName);
    void disposeNode(Node *node); 
    
    void registerNodeType(NodeType *newType);
    void unregisterNodeType(NodeType *type);
    
    //
    std::list<std::string>  nodeTypeNames();    

private:
    std::list<NodeType*>    m_nodeTypes;
};


#endif//NODECOLLECTION_H
