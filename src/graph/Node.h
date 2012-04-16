#ifndef NODE_H
#define NODE_H

#include "Plug.h"
#include "PlugLink.h"
#include "Parameter.h"
#include "Graph.h"
#include "Identifier.h"
#include "Types.h"
#include "NodeType.h"

class Node : public Identifier<NodeType>
{
    // List of functions able to access an instance of Node
    template<typename T> friend const char * const TypeName(T*);

public:
    // NOTE : may be this function can be protected
    Node(const std::string &name, size_t id, const NodeType *type)
    : Identifier<NodeType>(name, id, type)
    , m_owner(NULL) 
    {};
    virtual ~Node()
    {}

    typedef size_t  NodeId;

protected:
    void addInput(const std::string &name);
    void addOutput(const std::string &name);
    void addParameter(const std::string &name);

    void connect(Plug *src, Plug *dst);

protected:
    // type name
    const char * typeName() const {return TypeName(m_type);} 

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
