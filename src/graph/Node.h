#ifndef NODE_H
#define NODE_H

#include "Plug.h"
#include "PlugLink.h"
#include "Parameter.h"
#include "Graph.h"
#include "Identifier.h"

typedef int NodeType; // TODO

class Node : public Identifier<NodeType>
{
public:
    // NOTE : may be this function can be protected
    Node(const std::string &name, size_t id, NodeType *type)
    : Identifier<NodeType>(name, id, type)
    , m_owner(NULL)
    {};
    virtual ~Node()
    {}

    typedef NodeType    TypeInfo;
    typedef Node        OwnerType;
    typedef size_t      NodeId;

protected:
    void addInput();
    void addOutput();
    void addParameter();

    void connect();

private:
    // inputs/outputs of the node
    std::vector<Plug*>          m_inputs;
    std::vector<Plug*>          m_outputs;
    std::vector<Parameter*>     m_parameters;

    // Dataflow inside the node
    Graph<Plug, PlugLink>           m_dataFlowGraph;
    // Nodes inside this node
    std::vector<Node*>          m_nodes;
    // Owner of this node
    Node                        *m_owner;
};

#endif//NODE_H
