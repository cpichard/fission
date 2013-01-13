%{
#define SWIG_FILE_WITH_INIT
#include "ComputeEngine.h"
%}

class ComputeEngine 
{
public:
    ComputeEngine();
    ~ComputeEngine();
    // Test
    Status compute_async(Node &, Context &);
    Status compute(Node &, Context &);
};

