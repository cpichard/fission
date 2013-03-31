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

/// A plug is an node dynamic entry, input or output.
/// It's a in a dataflow graph owned by a module


class Plug : public Vertex, public ObjectId<PlugType>
{
    friend class Node;
    friend class Module;
    template<typename T> friend Node * Owner(T &);
    template<typename T> friend Node * Owner(T *);
public:
    Plug(const std::string &name, size_t id, const PlugType *info)
    : Vertex()
    , ObjectId<PlugType>(name, id, info) {}
    virtual ~Plug(){}

protected:
    /// The node the plug belongs to
    Node    *m_owner;
};



inline bool IsInput(Plug *p){return p ? p->m_type==&PlugInputType:false;}
inline bool IsOutput(Plug *p){return p ? p->m_type==&PlugOutputType:false;}
inline bool IsParameter(Plug *p){return p ? p->m_type==&PlugParameterType:false;}



// TODO : move blow code to Owner.h if more than one class is using it
template<typename T> Node * Owner(T &v){return v.m_owner;}
template<typename T> Node * Owner(T *v){return v ? v->m_owner:NULL;}

}; // namespace fission
#endif//PLUG_H
