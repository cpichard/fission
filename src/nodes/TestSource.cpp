#include "TestSource.h"
#include "Parameter.h"
#include "Types.h"

namespace fission {
// Name of the node
const char * const TestSource::s_typeName = "TestSource";

// No inputs for this node
const NodeDesc::Input  TestSource::s_inputs[]   = {};

// Only one output, the value of the parameter
const NodeDesc::Output TestSource::s_outputs[]  =
{
    // TEST
    NodeDesc::Output("Value","float")
};

// TODO : only one parameter
const NodeDesc::Param TestSource::s_params[]   =
{
    NodeDesc::Param("val", "float", "standard" )
};

// Version of the
const unsigned int TestSource::s_version = 0;

//size_t TestSource::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestSource::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}


}; // namespace fission
