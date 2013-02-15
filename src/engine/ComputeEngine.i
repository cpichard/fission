%{
#define SWIG_FILE_WITH_INIT
#include "ComputeEngine.h"
%}


namespace fission {
class ComputeEngine 
{
public:
    ComputeEngine();
    ~ComputeEngine();
    // Test
    Status compute(fission::Node &, fission::Context &);
};
};
