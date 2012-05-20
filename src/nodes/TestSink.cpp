#include "TestSink.h"
#include "Parameter.h"
#include "StandardTypes.h"

namespace fission {

// Name of the node type
const char * const TestSink::s_typeName = "TestSink";

/// Version of this node type
const unsigned int TestSink::s_version = 0;

// One inputs for this node
const NodeDesc::Input  TestSink::s_inputs[] = {
    NodeDesc::Input("value", Type<Float>())
};

// No outputs
//const NodeDesc::Output TestSink::s_outputs[]  = {};

// TODO : no parameter
const NodeDesc::Param TestSink::s_params[]   = {};


}; // namespace fission
