#include "TestValue.h"


const char * const TestValue::s_typeName = "TestValue";

TestValue::TestValue(const std::string &name)
: Node(name)
{
    addInput("input", Float);
    addOutput("output", Float);
//    addParameter("value", Float);    
}

TestValue::~TestValue()
{}
