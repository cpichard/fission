#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include "Node.h"

class Engine 
{
public:
    Engine();
    ~Engine();

    Status compute_async(Node &, Context &);
    Status compute(Node &, Context &);

private:
    // Graph of processing nodes
    // TODO : remove, engine is only use to compute stuff
    // TODO : make a "Document" class, or Group or Graph... 
    // whatever can store list of nodes and do search, etc..
    std::list<Node*>    m_nodes;

    // std::list<Task*>
    // CacheManager
    // EventManager
    // Scheduler, etc...
};

#endif//ENGINE_H
