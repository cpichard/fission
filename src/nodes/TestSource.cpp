#include "TestSource.h"


ImplementNode(TestSource) 

ImplementOutputs(TestSource, NewOutput("Value", Float))
ImplementInputs(TestSource)
ImplementParams(TestSource, NewParam("val", Float))


