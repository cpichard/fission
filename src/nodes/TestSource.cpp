#include "TestSource.h"
#include "engine/Context.h"

ImplementNode(TestSource)

ImplementOutput(TestSource, NewOutput("Value", Float))
ImplementInputs(TestSource)

ImplementParams(TestSource,
    NewParam("val", Int),
    NewParam("file", String))

extern "C" {
double TestSource_execute(fission::Context ctx, int val, const char *file)
{
    double tmp=0;
    for(int i=0; i < ctx.m_first;i++)
    {
        tmp=tmp+1.0;
    }
    return tmp;
};
};
