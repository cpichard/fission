#ifndef PLUGLINK_H
#define PLUGLINK_H

#include "Graph.h"
#include "Plug.h"
#include <string>

typedef int PlugLinkType; // TODO

struct PlugLink : public Edge<Plug>, Identifier<PlugLink>
{
public:
    PlugLink(const std::string &name, size_t id, PlugLinkType *typeinfo)
    : Edge()
    , Identifier(name, id, typeinfo)
    {}
    ~PlugLink(){}

    typedef PlugLinkType            TypeInfo;    
    typedef Graph<Plug, PlugLink>   OwnerType;
};

#endif//PLUGLINK_H
