#include "ParameterTest.h"
#include "Parameter.h"
#include "Module.h"
#include "TestOp.h"
#include "TestSource.h"
#include "TestSink.h"
#include "Name.h"

using namespace fission;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParameterTest );

ParameterTest::ParameterTest(){}

void ParameterTest::setUp()
{}

void ParameterTest::tearDown()
{}

void ParameterTest::testCreateParameter()
{
    // Build a module of node
    Module module("test1");
    module.registerNodeDesc(new TestSource());

    // Create an non typed node.
    Node *nodeUnknown = module.createNode("unknown", "");

    // This node should not exist
    CPPUNIT_ASSERT(nodeUnknown == NULL);

    Node *nodeTestSource = module.createNode("TestSource", "test1");

    //nodeTestSource->setValue()

}

