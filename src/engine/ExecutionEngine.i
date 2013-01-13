%{
#define SWIG_FILE_WITH_INIT
#include "ExecutionEngine.h"
%}

class ExecutionEngine 
{
public:
    ExecutionEngine();
    ~ExecutionEngine();
    // Test
    Status compute_async(Node &, Context &);
    Status compute(Node &, Context &);
};

