#ifndef NODE_H
#define NODE_H

#include "Plug.h"
#include "PlugLink.h"
#include "Parameter.h"
#include "Graph.h"
#include "ObjectId.h"
#include "NodeDesc.h"
#include "rtts/Type.h"
#include "rtts/Value.h"

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
    friend size_t NbInputs(Node *node);
    friend size_t NbParameters(const Node &node);
    friend size_t NbParameters(Node *node);
    friend inline Plug * Output(Node *node);
    friend inline Plug * Output(Node &node);
    friend inline Plug * Input0(Node *node);
    friend inline Plug * Input0(Node &node);
    friend inline Plug * Input1(Node *node);
    friend inline Plug * Input1(Node &node);
    friend inline Parameter * Param0(Node *);
    friend inline Parameter * Param1(Node *);
    friend inline Parameter * Param2(Node *);

public:
    // NOTE : may be this function can be protected
    Node(const std::string &name, const NodeDesc *type);
    virtual ~Node(){}


    // Parameter modifications
    //void change(Parameter, ModificationType, values....)
    //void change(Parameter, Context, ModificationType, values....)
    //void change(ParameterName, Context, ModificationType, values....)
    //void apply(Parameter *, const ParameterModification &pm);


    // TODO : set value by name
    ///void setValue(size_t paramNb, Value &val, Context *c=0);

    // Typedefs

    /// Get contained nodes
    const std::vector<Node*> & getNodes() const {return m_nodes;}

protected:
    // Note : is it still usefull as now, we don't inherit new nodes from this class?
    //void addInput(const char *name, const PlugType *);
    //void addOutput(const char *name, const PlugType *);
    //void addParameter(const std::string &name,  *);

    // Non checked accesssors
    inline Plug*        input(size_t i){return m_inputPlugs[i];}
    inline Plug*        output(){return m_outputPlugs;}
    inline Parameter*   param(size_t i){return m_parameterPlugs[i];}
protected:
    // type name
    const char * typeName() const {return TypeName(m_type);}

    // inputs/outputs of the node
    Plug*                       m_outputPlugs;
    std::vector<Plug*>          m_inputPlugs;
    std::vector<Parameter*>     m_parameterPlugs;

    // Nodes embedded in this node
    std::vector<Node*>          m_nodes;

    // Owner of this node, generally a Module
    Node                        *m_owner;
    // Note : may be I can have the collection node link
    // Node *m_module;
};

inline size_t NbInputs(const Node &node){return node.m_inputPlugs.size();}
inline size_t NbInputs(Node *node){return node->m_inputPlugs.size();}

inline size_t NbParameters(const Node &node) {return node.m_parameterPlugs.size();}
inline size_t NbParameters(Node *node) {return node->m_parameterPlugs.size();}


inline Plug * Output(Node *node){return node ? node->m_outputPlugs:NULL;}
inline Plug * Input0(Node *node){return node ? node->m_inputPlugs[0]:NULL;}
inline Plug * Input1(Node *node){return node ? node->m_inputPlugs[1]:NULL;}

inline Plug * Output(Node &node){return node.m_outputPlugs;}
inline Plug * Input0(Node &node){return node.m_inputPlugs[0];}
inline Plug * Input1(Node &node){return node.m_inputPlugs[1];}

inline Parameter * Param0(Node *node){return node->m_parameterPlugs[0];}
inline Parameter * Param1(Node *node){return node->m_parameterPlugs[1];}
inline Parameter * Param2(Node *node){return node->m_parameterPlugs[2];}


}; // namespace fission
#endif//NODE_H
