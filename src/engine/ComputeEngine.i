%{
#include "engine/ComputeEngine.h"
#include "graph/Module.h"
%}


namespace fission {
class ComputeEngine 
{
public:
    ComputeEngine(fission::JITEngine &);
    ~ComputeEngine();

    Status run(fission::Node &, const fission::Context &);
};
};
