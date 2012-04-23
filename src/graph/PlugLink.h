#ifndef PLUGLINK_H
#define PLUGLINK_H

#include "Graph.h"
#include "Plug.h"
#include <string>

typedef int PlugLinkType; // TODO

struct PlugLink : public Edge, public ObjectId<PlugLinkType>
{
public:
    PlugLink(const std::string &name
            , size_t id
            , PlugLinkType *typeinfo
            , Vertex *src
            , Vertex *dst)
    : Edge(src, dst)
    , ObjectId<PlugLinkType>(name, id, typeinfo)
    {}
    ~PlugLink(){}
};

#endif//PLUGLINK_H
