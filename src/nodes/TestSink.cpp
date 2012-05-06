#include "TestSink.h"
#include "Parameter.h"
#include "Types.h"

namespace fission {
// Name of the node
const char * const TestSink::s_typeName = "TestSink";

// No inputs for this node
const NodeDesc::Input  TestSink::s_inputs[]   =
{
    NodeDesc::Input("value", "float")
};

// Only one output, the value of the parameter
//const NodeDesc::Output TestSink::s_outputs[]  = {};

// TODO : only one parameter
const NodeDesc::Param TestSink::s_params[]   = {};

// Version of the
const unsigned int TestSink::s_version = 0;

}; // namespace fission
