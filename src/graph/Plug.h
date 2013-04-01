#ifndef PLUG_H
#define PLUG_H

#include "Vertex.h"
#include "ObjectId.h"
namespace fission {

// 2 pointers for a plug type, input or output
typedef int PlugType;
extern const PlugType PlugInputType;
extern const PlugType PlugOutputType;
extern const PlugType PlugParameterType;

class Node;
class BaseType;

/// A plug is an node dynamic entry, input or output.
/// It's a in a dataflow graph owned by a module

class Plug : public Vertex, public ObjectId<PlugType> {

    friend class Node;
    friend class Module;
    template<typename T> friend Node * Owner(T &);
    template<typename T> friend Node * Owner(T *);
    template <typename V> friend const BaseType * ValueTypeOf(const V &v);
    template <typename V> friend const BaseType * ValueTypeOf(V *v);

public:
    Plug(const std::string &name, const PlugType *info, const BaseType *valueType)
    : Vertex()
    , ObjectId<PlugType>(name, info) 
    , m_owner(0)
    , m_valueType(valueType) {}

    virtual ~Plug(){}

protected:
    /// The node the plug belongs to
    Node                *m_owner;       // 8
    const BaseType      *m_valueType;   // 8
                                //Vertex  32
                                //ObjectId 20

    // 1 Plug ~= 68 bytes on a 64bits machine
    // 1000 nodes
    // 20 plugs per nodes
    //20 000 plugs => 1.8 Mb
};



inline bool IsInput(Plug *p){return p ? p->m_type == &PlugInputType : false;}
inline bool IsOutput(Plug *p){return p ? p->m_type == &PlugOutputType : false;}
inline bool IsParameter(Plug *p){return p ? p->m_type == &PlugParameterType : false;}



// TODO : move blow code to Owner.h if more than one class is using it
template<typename T> Node * Owner(T &v){return v.m_owner;}
template<typename T> Node * Owner(T *v){return v ? v->m_owner:NULL;}

}; // namespace 
#endif//PLUG_H
