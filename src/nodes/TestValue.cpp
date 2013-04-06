

#include "TestValue.h"
#include "engine/Context.h"

ImplementNode(TestValue)

ImplementOutput(TestValue, NewOutput("Value", Float))
ImplementInputs(TestValue)

ImplementParams(TestValue,
    NewParam("float", Float),
    NewParam("int", Int),
    NewParam("string", String))

extern "C" {
double TestValue_execute(fission::Context ctx, int val, const char *file)
{
    double tmp=0;
    for(int i=0; i < ctx.m_first;i++)
    {
        tmp=tmp+1.0;
    }
    return tmp;
};
};

