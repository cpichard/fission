#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <list>
#include "Node.h"
#include "Status.h"
#include "Context.h"

namespace fission {

class ExecutionEngine
{
public:
    ExecutionEngine();
    ~ExecutionEngine();

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
}; // namespace fission
#endif//EXECUTIONENGINE_H
