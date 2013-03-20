#include "TestSink.h"
#include "engine/Context.h"
#include <cstdio>

ImplementNode(TestSink) 

ImplementOutputs(TestSink, NewOutput("IO", Float))
ImplementInputs(TestSink, NewInput("value", Float))
ImplementParams(TestSink)

extern "C" {
double TestSink_execute(const fission::Context ctx, double a){
    printf("sink received: %g\n", a);
    // Returning a because we don't handle functions returning void atm
    return a;
}
};

