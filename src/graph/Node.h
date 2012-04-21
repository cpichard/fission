#ifndef NODE_H
#define NODE_H

#include "Plug.h"
#include "PlugLink.h"
#include "Parameter.h"
#include "Graph.h"
#include "ObjectId.h"
#include "Types.h"
#include "NodeType.h"

class Node : public ObjectId<NodeType>
{
    // List of functions able to access an instance of Node
    template<typename T> friend const char * const TypeName(T*);
    friend size_t NbInputs(const Node &node);
    friend size_t NbOutputs(const Node &node);
    friend size_t NbInputs(Node *node);
    friend size_t NbOutputs(Node *node);

public:
    // NOTE : may be this function can be protected
    Node(const std::string &name, size_t id, const NodeType *type);
    virtual ~Node(){}

    // Typedefs
    typedef size_t  NodeId;

protected:
    void addInput(const std::string &name, PlugType *);
    void addOutput(const std::string &name, PlugType *);
    void addParameter(const std::string &name);

    void connect(Plug *src, Plug *dst);

protected:
    // type name
    const char * typeName() const {return TypeName(m_type);} 

    // inputs/outputs of the node
    std::vector<Plug*>          m_inputs;
    std::vector<Plug*>          m_outputs;
    std::vector<Parameter*>     m_parameters;

    // Dataflow inside the node TODO : in the module instead
    Graph<Plug, PlugLink>           m_dataFlowGraph;
    
    // Note : may be I can have the collection node link
    // Node *m_module;

    // Nodes embedded in this node
    std::vector<Node*>          m_nodes;

    // Owner of this node
    Node                        *m_owner;
};

inline size_t NbInputs(const Node &node){return node.m_inputs.size();}
inline size_t NbOutputs(const Node &node){return node.m_outputs.size();}
inline size_t NbInputs(Node *node){return node->m_inputs.size();}
inline size_t NbOutputs(Node *node){return node->m_outputs.size();}

#endif//NODE_H
