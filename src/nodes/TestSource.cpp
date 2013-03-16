#include "TestSource.h"
#include "Parameter.h"
#include "StandardTypes.h"
#include <iostream>


ImplementNode(TestSource) 

ImplementOutputs(TestSource, NewOutput("Value", Float))
ImplementInputs(TestSource)
ImplementParams(TestSource, NewParam("val", Float))


