#ifndef NODEDESC_H
#define NODEDESC_H

namespace llvm {
class Module;
};

namespace fission {

class BaseType;

/// A node description is the base class for all new types of node.
/// It is used to describe node input/outputs, parameters and functions
/// The node type defines structures ....
/// ...

class NodeDesc
/// TODO : is it a NodeBaseType that inherits from BaseType ?
/// So it's directly in the type system
{
    // Friend functions
    template<typename NT> friend inline size_t NbInputs();
    template<typename NT> friend inline size_t NbOutputs();
    template<typename NT> friend inline size_t NbParameters();

public:
    /// Input/Output of a node structure definition
    struct IODesc
    {
        IODesc(const char *name, const BaseType *type)
        : m_name(name)
        , m_type(type)
        {}
        const char      *m_name;
        const BaseType  *m_type; // TODO : PlugType ??
    };

    // Input and output definition
    typedef struct IODesc Output;
    typedef struct IODesc Input;

    struct ParamDesc
    {
        ParamDesc(const char *name, const BaseType *type, const void *prop)
        : m_name(name)
        , m_type(type)
        , m_prop(prop)
        {}
        const char      *m_name;
        const BaseType  *m_type; /// Might change to a pointer to a structure
        const void      *m_prop; /// Properties
    };
    typedef struct ParamDesc Param;

    /// All derived nodetypes must implement these functions
    /// to define a new node type
    virtual const char * typeName() const=0;

    virtual const NodeDesc::Input * inputs() const=0;
    virtual const NodeDesc::Output * outputs() const=0;
    virtual const NodeDesc::Param * parameters() const=0;

    virtual size_t nbInputs() const=0;
    virtual size_t nbOutputs() const=0;
    virtual size_t nbParameters() const=0;

    // LLVM generated IR code
    virtual void registerFunctions(llvm::Module *)=0;
};

typedef NodeDesc::Output NodeOutput;
typedef NodeDesc::Input NodeInput;
typedef NodeDesc::Param NodeParameter;

/// Functions to access node description infos from an instance or from
/// the class itself.

template<typename NT>
inline size_t NbInputs(){return NT::s_nbInputs;}

template<typename NT>
inline size_t NbOutputs(){return NT::s_nbOutputs;}

template<typename NT>
inline size_t NbParameters(){return NT::s_nbParameters;}

inline size_t NbInputs(const NodeDesc *node){return node->nbInputs();}

inline size_t NbOutputs(const NodeDesc *node){return node->nbOutputs();}

inline size_t NbParameters(const NodeDesc *node){return node->nbParameters();}

template<typename NT>
inline const NodeDesc::Input * Inputs(const NT *nodetype){return nodetype->inputs();}

template<typename NT>
inline const NodeDesc::Output * Outputs(const NT *nodetype){return nodetype->outputs();}

template<typename NT>
inline const NodeDesc::Param * Parameters(const NT *nodetype){return nodetype->parameters();}
}; // namespace fission

#endif//NODEDESC_H
