#include "TestSink.h"
#include "Parameter.h"
#include "StandardTypes.h"


#include <iostream>
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

//extern "C"
//double printd(double X) {
//  printf("result=%f\n", X);
//  return 0;
//}


const char * TestSink::getIrFile() const {return "TestSink_s.s";}



}; // namespace fission
