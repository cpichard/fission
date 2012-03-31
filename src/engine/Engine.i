%{
#define SWIG_FILE_WITH_INIT
#include "Engine.h"
%}

class Engine 
{
public:
    Engine();
    ~Engine();
    // Test
    Status compute_async(Node &, Context &);
    Status compute(Node &, Context &);
};

