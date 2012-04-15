#ifndef NODECOLLECTION_H
#define NODECOLLECTION_H

class NodeCollection : public Node
{
public:
    NodeCollection(const std::string &name)
    : Node(name, 0, NULL){}
    ~NodeCollection(){}

    NodeId createNode(const std::string &nodeName, const std::string *nodeTypeName);
    void disposeNode(NodeId node); 
    
    registerNewNodeType();
    unregisterNewNodeType();
    nodeTypes();    

private:
    std::list<NodeType*>    m_nodeTypes;
};


#endif//NODECOLLECTION_H
