#include "TestValue.h"
#include "Parameter.h"
#include "Types.h"

namespace fission {

// Name of the node
const char * const TestValue::s_typeName = "TestValue";

// No inputs for this node
const NodeDesc::Input  TestValue::s_inputs[]   = {};

// Only one output, the value of the parameter
const NodeDesc::Output TestValue::s_outputs[]  = 
{   
    // TEST
    NodeDesc::Output("Value","float") 
};

// TODO : only one parameter
const NodeDesc::Param TestValue::s_params[]   = {};

// Version of the 
const unsigned int TestValue::s_version = 0;

//size_t TestValue::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestValue::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}

}; //namespace fission

