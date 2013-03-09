#include "TestSource.h"
#include "Parameter.h"
#include "StandardTypes.h"
#include <iostream>

namespace fission {

// Name of the node
const char * const TestSource::s_typeName = "TestSource";

// Version of the
const unsigned int TestSource::s_version = 0;

// No inputs for this node
const NodeInput
TestSource::s_inputs[] = {};

// Only one output, the value of the parameter
const NodeOutput
TestSource::s_outputs[] = {
    NodeOutput("Value", Type<Float>()),
};

// TODO : only one parameter
const NodeParameter
TestSource::s_params[] = {
    // TODO ...
    NodeParameter("val", Type<Float>(), "standard"),
};


//size_t TestSource::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestSource::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}

const char * TestSource::getIrFile() const {return "TestSource_s.s";}

}; // namespace fission
