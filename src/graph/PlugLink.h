#ifndef PLUGLINK_H
#define PLUGLINK_H

#include "Graph.h"
#include "Plug.h"
#include <string>

namespace fission {

typedef int PlugLinkType; 
extern const PlugLinkType InternalLink; // Link internal to a node
extern const PlugLinkType ExternalLink; // Link between nodes
extern const PlugLinkType ParameterLink;// Links between parameters

struct PlugLink : public Edge, public ObjectId<PlugLinkType>
{
public:
    PlugLink(const std::string &name
            , PlugLinkType *typeinfo
            , Vertex *src
            , Vertex *dst)
    : Edge(src, dst)
    , ObjectId<PlugLinkType>(name, typeinfo)
    {}
    ~PlugLink(){}
};

}; // namespace fission
#endif//PLUGLINK_H
