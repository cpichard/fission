#ifndef COMPUTEENGINE_H
#define COMPUTEENGINE_H

#include <list>
#include "Node.h"
#include "Status.h"
#include "Context.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"

namespace fission {

class ComputeEngine
{
public:
    ComputeEngine();
    ~ComputeEngine();

    Status compute(Node &, Context &);

private:


    // std::list<Task*>
    // CacheManager
    // EventManager
    // Scheduler, etc...
};
}; // namespace fission
#endif//COMPUTEENGINE_H
