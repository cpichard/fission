#ifndef NODEDESC_H
#define NODEDESC_H

/// A node description is the base class for all new types of node.
/// The node type defines structures ....
/// ...

class NodeDesc
{
    // Friend functions
    template<typename NT> friend inline size_t NbInputs();
    template<typename NT> friend inline size_t NbOutputs();

public: 
    // IO structure definition
    struct IODesc 
    {   
        IODesc(const char *name, const char *type)
        : m_name(name)
        , m_type(type)
        {}
        const char *m_name; 
        const char *m_type;
    };

    // Input and output definition
    typedef struct IODesc Output;
    typedef struct IODesc Input;

    /// All derived nodetypes must implement these functions
    /// to define a new node type
    virtual const char * typeName() const=0; 
    
    virtual const NodeDesc::Input * inputs() const = 0; 
    virtual const NodeDesc::Output * outputs() const  = 0;
    
    virtual size_t nbInputs() const = 0; 
    virtual size_t nbOutputs() const = 0; 

    // TODO parameter description 
    struct Param {const char *inputName; int inputType;};
};

/// Functions to access node description infos from an instance or from
/// the class itself.

template<typename NT>
inline size_t NbInputs(){return NT::s_nbInputs;}

template<typename NT>
inline size_t NbOutputs(){return NT::s_nbOutputs;}

inline size_t NbInputs(const NodeDesc *node){return node->nbInputs();}

inline size_t NbOutputs(const NodeDesc *node){return node->nbOutputs();}

template<typename NT>
inline const NodeDesc::Input * Inputs(const NT *nodetype){return nodetype->inputs();}

template<typename NT>
inline const NodeDesc::Output * Outputs(const NT *nodetype){return nodetype->outputs();}

#endif//NODEDESC_H
