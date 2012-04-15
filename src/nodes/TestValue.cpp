#include "TestValue.h"
#include "Parameter.h"
#include "Types.h"

const char * const TestValue::s_typeName = "TestValue";

NodeType testValueType = 9;

TestValue::TestValue(const std::string &name)
: Node(name, 0, &testValueType)
{
    //addInput("input", Float);
    //addOutput("output", Float);
//    addParameter("value", Float);    
}

TestValue::~TestValue()
{}
