#include "TestOp.h"
#include "Parameter.h"
#include "Status.h"
#include "StandardTypes.h"
#include "Value.h"

namespace fission {

/// Name of the node
const char * const TestOp::s_typeName = "TestOp";

/// Version of the node
const unsigned int TestOp::s_version = 0;

// One input for this node
const NodeDesc::Input  TestOp::s_inputs[] = {
    NodeDesc::Input("InValue1", Type<Float>()),
    NodeDesc::Input("InValue2", Type<Float>()),
};

// Only one output, the value of the parameter
const NodeDesc::Output TestOp::s_outputs[] = {
    // TEST
    NodeDesc::Output("OutValue", Type<Float>())
};

// TODO : no parameter
const NodeDesc::Param TestOp::s_params[] = {};

// First test function
Status execute(const Value *in, Value &out) {
    // Do something really cool !
    out = in[0];

    return SUCCESS;
}


}; // namespace fission

