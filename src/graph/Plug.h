#ifndef PLUG_H
#define PLUG_H

#include "Vertex.h"
#include "ObjectId.h"

typedef int PlugType;    

class Node;

class Plug : public Vertex<Plug>, ObjectId<PlugType>
{
    friend class Node;

public:
    Plug(const std::string &name, size_t id, const PlugType *info)
    : Vertex<Plug>()
    , ObjectId<PlugType>(name, id, info) {}
    virtual ~Plug(){}

protected:
    Node    *m_owner;
};

#endif//PLUG_H
