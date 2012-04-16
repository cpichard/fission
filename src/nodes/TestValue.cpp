#include "TestValue.h"
#include "Parameter.h"
#include "Types.h"

// Name of the node
const char * const TestValue::s_typeName = "TestValue";

// No inputs for this node
const NodeType::Input  TestValue::s_inputs[]   = {};

// Only one output, the value of the parameter
const NodeType::Output TestValue::s_outputs[]  = 
{   
    NodeType::Output("Value","float") 
};

// TODO : only one parameter
const NodeType::Param TestValue::s_params[]   = {};

// Version of the 
const unsigned int TestValue::s_version = 0;

size_t TestValue::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeType::Input);}
size_t TestValue::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeType::Output);}



