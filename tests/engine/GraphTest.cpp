#include "GraphTest.h"
#include "NodeCollection.h"
#include "TestValue.h"
#include "Types.h"
#include "Name.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( GraphTest );

GraphTest::GraphTest(){}

void GraphTest::setUp()
{}

void GraphTest::tearDown()
{}

void GraphTest::testCreateNode()
{
    // Build a graph of node
    NodeCollection graph("test1");
    graph.registerNodeType(new TestValue());
    
    // Create an non typed node. 
    Node *nodeUnknown = graph.createNode("unknown", "");
    
    // This node should not exist 
    CPPUNIT_ASSERT(nodeUnknown == NULL);

    Node *nodeTestValue = graph.createNode("TestValue", "test1");
    CPPUNIT_ASSERT(nodeTestValue != NULL);
    CPPUNIT_ASSERT(TypeName(nodeTestValue) == TypeName<TestValue>());

    // Test name
    CPPUNIT_ASSERT(Name(*nodeTestValue) == "test1");
    CPPUNIT_ASSERT(Name(nodeTestValue) == "test1");

    //CPPUNIT_ASSERT( NbInputs(nodeTestValue) == 0);
    //CPPUNIT_ASSERT( NbOutputs(nodeTestValue) == 1);
    //CPPUNIT_ASSERT( NbOutputs<TestValue>() == 1);
}

// TODO 
void GraphTest::testGetNode()
{
    // Build a graph of node
    NodeCollection graph("test1");
    
    // Create an non typed node. 
    Node *node1 = graph.createNode("TestValue", "node1");
    Node *node2 = graph.createNode("TestValue", "node2");
    Node *node3 = graph.createNode("TestValue", "node3");
    Node *node4 = graph.createNode("TestValue", "node4");

    // Get nodes of the graph
    // std::vector<Node&> nodes = graph.getNodeNames()
}

void GraphTest::testConnectNodes()
{
    // Build a graph of node
    NodeCollection graph("test1");
    
    // Create an non typed node. 
    Node *node1 = graph.createNode("TestValue", "node1");
    Node *node2 = graph.createNode("TestValue", "node2");

    // Connect nodes
    //graph.connect( Outputs(node1, 0), node1), Input(0, node2));
    //graph.connect( Output0(node1), Input(0, node2));
    // TODO graph.connect( Output(node1, "output"), Input(node2, "input"));
    //graph.connect( node1.output(0), node2.input(0));

    // test connection
    //std::vector<int> v;
    //v[1] = 2;
}


void GraphTest::testGraphName()
{
    NodeCollection graph("test1");
    CPPUNIT_ASSERT( Name(graph) == "test1" );
}


