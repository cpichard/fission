#ifndef COMPUTEENGINE_H
#define COMPUTEENGINE_H

#include <list>
#include "Module.h"
#include "Node.h"
#include "Status.h"
#include "Context.h"

namespace fission {

class ComputeEngine
{
public:
    ComputeEngine();
    ~ComputeEngine();

    Status compute(Module &, Node &, const Context &);

private:


    // std::list<Task*>
    // CacheManager
    // EventManager
    // Scheduler, etc...
};
}; // namespace fission
#endif//COMPUTEENGINE_H
