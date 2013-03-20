#include "TestSource.h"
#include "engine/Context.h"

ImplementNode(TestSource) 

ImplementOutputs(TestSource, NewOutput("Value", Float))
ImplementInputs(TestSource)
ImplementParams(TestSource, NewParam("val", Float))

extern "C" {
double TestSource_execute(fission::Context ctx)
{
    double tmp=0;
    for(int i=0; i < ctx.m_first;i++)
    {
        tmp=tmp+1.0;
    }
    return tmp;
};
};
