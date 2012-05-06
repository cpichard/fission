#ifndef PLUG_H
#define PLUG_H

#include "Vertex.h"
#include "ObjectId.h"
namespace fission {

/// WIP
/// Should implement the different kind of plug we will have
typedef int PlugType;

class Node;

/// A plug is an node dynamic entry, input or output.
/// It's a in a dataflow graph owned by a module


class Plug : public Vertex, public ObjectId<PlugType>
{
    friend class Node;
    friend class Module;
public:
    Plug(const std::string &name, size_t id, const PlugType *info)
    : Vertex()
    , ObjectId<PlugType>(name, id, info) {}
    virtual ~Plug(){}

protected:
    /// The node the plug belongs to
    Node    *m_owner;
};
}; // namespace fission
#endif//PLUG_H
