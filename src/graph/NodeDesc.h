#ifndef NODEDESC_H
#define NODEDESC_H

#include <cstdlib> // size_t
#include <iostream>

namespace llvm {
class Linker;
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
     //   , m_prop(prop)
        {}
        const char      *m_name;
        const BaseType  *m_type; /// Might change to a pointer to a structure
    //    const void      *m_prop; /// Properties
    };
    typedef struct ParamDesc Param;

    /// All derived nodetypes must implement these functions
    /// to define a new node type
    virtual const char * typeName() const=0;

    virtual const NodeDesc::Input * inputs() const=0;
    virtual const NodeDesc::Output * output() const=0;
    virtual const NodeDesc::Param * parameters() const=0;

    virtual size_t nbInputs() const=0;
    virtual size_t nbParameters() const=0;

    // llvm ir file
    virtual const char * getIrFile() const=0;

    //
    virtual ~NodeDesc(){}

};

typedef NodeDesc::Output NodeOutput;
typedef NodeDesc::Input NodeInput;
typedef NodeDesc::Param NodeParameter;

/// Functions to access node description infos from an instance or from
/// the class itself.

template<typename NT>
inline size_t NbInputs(){return NT::s_nbInputs;}

template<typename NT>
inline size_t NbParameters(){return NT::s_nbParameters;}

inline size_t NbInputs(const NodeDesc *node){return node->nbInputs();}

inline size_t NbParameters(const NodeDesc *node){return node->nbParameters();}

template<typename NT>
inline const NodeDesc::Input * Inputs(const NT *nodetype){return nodetype->inputs();}

template<typename NT>
inline const NodeDesc::Output * Output(const NT *nodetype){return nodetype->output();}

template<typename NT>
inline const NodeDesc::Param * Parameters(const NT *nodetype){return nodetype->parameters();}
}; // namespace fission

// ============== Macros to make a new node ==================

// StandardTypes is used in the macros
#include <rtts/StandardTypes.h>
#include <string>

#define DeclareNewNode(NodeName, nbIn, nbOut, nbParam) \
namespace fission {\
class NodeName: public NodeDesc \
{ \
    template<typename T> friend const char * const TypeName(); \
    template<typename NT> friend inline size_t NbInputs(); \
    template<typename NT> friend inline size_t NbParameters(); \
public: \
    const char * typeName() const {return NodeName::s_typeName;} \
    const NodeDesc::Input * inputs() const {return s_inputs;} \
    const NodeDesc::Output * output() const {return s_output;} \
    const NodeDesc::Param * parameters() const {return s_params;} \
    inline size_t nbInputs() const {return NodeName::s_nbInputs;}; \
    inline size_t nbParameters() const {return NodeName::s_nbParams;}; \
    virtual const char * getIrFile() const; \
    static NodeName * getInstance();\
private: \
    NodeName(){}; \
    static const char * const       s_typeName; \
    static const size_t             s_nbInputs = nbIn; \
    static const size_t             s_nbParams = nbParam; \
    static const NodeDesc::Input    s_inputs[]; \
    static const NodeDesc::Output   s_output[]; \
    static const NodeDesc::Param    s_params[]; \
    static const unsigned int       s_version; \
    static NodeName                 *s_singleton; \
}; \
};\

#define NewOutput(val, typ) NodeDesc::Output(val, Type<typ>())
#define ImplementOutput(NodeName, ... ) \
namespace fission {\
const NodeDesc::Output NodeName::s_output[] = { \
    __VA_ARGS__\
};\
};\

#define NewInput(val, typ) NodeInput(val, Type<typ>())
#define ImplementInputs(NodeName, ... ) \
namespace fission {\
const NodeInput NodeName::s_inputs[] = { \
    __VA_ARGS__\
};\
};\

#define NewParam(val, typ) NodeDesc::Param(val, Type<fission::typ>(), "standard")
#define ImplementParams(NodeName, ... ) \
namespace fission {\
const NodeDesc::Param NodeName::s_params[] = { \
    __VA_ARGS__\
};\
};\


#define ImplementNode(NodeName) \
namespace fission {\
NodeName *NodeName::s_singleton=0; \
const char * const NodeName::s_typeName = #NodeName; \
const unsigned int NodeName::s_version = 0; \
const char * NodeName::getIrFile() const {return "NodeName_s.s";} \
NodeName * NodeName::getInstance()\
{\
    if(!s_singleton) {\
        s_singleton = new NodeName();\
    }\
    return s_singleton;\
}\
};\


#endif//NODEDESC_H
