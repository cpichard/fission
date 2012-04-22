#include "TestOp.h"
#include "Parameter.h"
#include "Types.h"

// Name of the node
const char * const TestOp::s_typeName = "TestOp";

// No inputs for this node
const NodeDesc::Input  TestOp::s_inputs[]   = {
    NodeDesc::Input("InValue","float") 
};

// Only one output, the value of the parameter
const NodeDesc::Output TestOp::s_outputs[]  = 
{   
    // TEST
    NodeDesc::Output("Value","float") 
};

// TODO : only one parameter
const NodeDesc::Param TestOp::s_params[]   = {};

// Version of the 
const unsigned int TestOp::s_version = 0;

//size_t TestOp::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestOp::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}



