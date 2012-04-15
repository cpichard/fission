#ifndef PLUGLINK_H
#define PLUGLINK_H

#include "Graph.h"
#include "Plug.h"
#include <string>

typedef int PlugLinkType; // TODO

struct PlugLink : public Edge<Plug>, Identifier<PlugLinkType>
{
public:
    PlugLink(const std::string &name, size_t id, PlugLinkType *typeinfo)
    : Edge<Plug>()
    , Identifier<PlugLinkType>(name, id, typeinfo)
    {}
    ~PlugLink(){}
};

#endif//PLUGLINK_H
