#ifndef PLUG_H
#define PLUG_H

#include "Vertex.h"
#include "Identifier.h"

typedef int PlugType;    

class Plug : public Vertex<Plug>, Identifier<Plug>
{
public:
    Plug(const std::string &name, size_t id, PlugType *info)
    : Vertex()
    , Identifier<Plug>(name, id, info) {}
    virtual ~Plug(){}
    
    //
    typedef PlugType TypeInfo;
    typedef Node    OwnerType;
};

#endif//PLUG_H
