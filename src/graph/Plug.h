#ifndef PLUG_H
#define PLUG_H

#include "Vertex.h"
#include "Identifier.h"

typedef int PlugType;    

class Plug : public Vertex<Plug>, Identifier<PlugType>
{
public:
    Plug(const std::string &name, size_t id, PlugType *info)
    : Vertex<Plug>()
    , Identifier<PlugType>(name, id, info) {}
    virtual ~Plug(){}
    
};

#endif//PLUG_H
