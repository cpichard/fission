#ifndef NODE_H
#define NODE_H

#include "Plug.h"
#include "PlugLink.h"
#include "Parameter.h"
#include "Graph.h"
#include "ObjectId.h"
#include "Type.h"
#include "NodeDesc.h"

namespace fission {

class Node : public ObjectId<NodeDesc>
{
    friend class Module;

    // List of functions able to access an instance of Node
    // This is to test a way of building the API with only
    // functions like Name(obj) or Input0(obj)
    // I think it's more readable
    // The ugly counter part is the code below
    // I might use and "#include NodeFriends.h"
    // or something more close to
    // IMPLEMENTS(Naming)
    // IMPLEMENTS(PlugIO)
    // IMPLEMENTS(Typeable)
    template<typename T> friend const char * const TypeName(T*);
    friend size_t NbInputs(const Node &node);
    friend size_t NbOutputs(const Node &node);
    friend size_t NbInputs(Node *node);
    friend size_t NbOutputs(Node *node);
    friend inline Plug * Output0(Node *node);
    friend inline Plug * Input0(Node *node);
    friend inline Plug * Output1(Node *node);
    friend inline Plug * Input1(Node *node);
    friend inline Plug * Output0(Node &node);
    friend inline Plug * Input0(Node &node);
    friend inline Plug * Output1(Node &node);
    friend inline Plug * Input1(Node &node);

public:
    // NOTE : may be this function can be protected
    Node(const std::string &name, size_t id, const NodeDesc *type);
    virtual ~Node(){}

    // Typedefs
    typedef size_t  NodeId;

protected:
    // Note : is it still usefull as now, we don't inherit new nodes from this class?
    //void addInput(const char *name, const PlugType *);
    //void addOutput(const char *name, const PlugType *);
    //void addParameter(const std::string &name,  *);

    // Non checked accesssors
    inline Plug* input(size_t i){return m_inputs[i];}
    inline Plug* output(size_t i){return m_outputs[i];}

protected:
    // type name
    const char * typeName() const {return TypeName(m_type);}

    // inputs/outputs of the node
    std::vector<Plug*>          m_inputs;
    std::vector<Plug*>          m_outputs;
    std::vector<Parameter*>     m_parameters;

    // Nodes embedded in this node
    std::vector<Node*>          m_nodes;

    // Owner of this node, generally a Module
    Node                        *m_owner;
    // Note : may be I can have the collection node link
    // Node *m_module;
};

inline size_t NbInputs(const Node &node){return node.m_inputs.size();}
inline size_t NbOutputs(const Node &node){return node.m_outputs.size();}
inline size_t NbInputs(Node *node){return node->m_inputs.size();}
inline size_t NbOutputs(Node *node){return node->m_outputs.size();}
inline Plug * Output0(Node *node){return node ? node->m_outputs[0]:NULL;}
inline Plug * Output1(Node *node){return node ? node->m_outputs[1]:NULL;}
inline Plug * Input0(Node *node){return node ? node->m_inputs[0]:NULL;}
inline Plug * Input1(Node *node){return node ? node->m_inputs[1]:NULL;}

inline Plug * Output0(Node &node){return node.m_outputs[0];}
inline Plug * Output1(Node &node){return node.m_outputs[1];}
inline Plug * Input0(Node &node){return node.m_inputs[0];}
inline Plug * Input1(Node &node){return node.m_inputs[1];}
}; // namespace fission
#endif//NODE_H
