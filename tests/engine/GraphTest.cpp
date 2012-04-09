#include "GraphTest.h"
#include "NodeGraph.h"
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
    NodeGraph graph("test1");
    
    // Create an non typed node. 
    Node &nodeUnknown = graph.createNode("unknown", "");
    
    // This node should be a NoOp type
    CPPUNIT_ASSERT( TypeName(nodeUnknown) == TypeName<Node>() );

    // 
    Node &nodeTestValue = graph.createNode("TestValue", "test1");

    //
    CPPUNIT_ASSERT( TypeName(nodeTestValue) == TypeName<TestValue>() );
}

// TODO 
void GraphTest::testGetNode()
{
    // Build a graph of node
    NodeGraph graph("test1");
    
    // Create an non typed node. 
    Node &node1 = graph.createNode("unknown", "node1");
    Node &node2 = graph.createNode("unknown", "node2");
    Node &node3 = graph.createNode("unknown", "node3");
    Node &node4 = graph.createNode("unknown", "node4");

    // Get nodes of the graph
    // std::vector<Node&> nodes = graph.getNodeNames()
}

void GraphTest::testConnectNodes()
{
    // Build a graph of node
    NodeGraph graph("test1");
    
    // Create an non typed node. 
    Node &node1 = graph.createNode("TestValue", "node1");
    Node &node2 = graph.createNode("TestValue", "node2");

    // Connect nodes
    //graph.connect( Output(node1, 0), Input(node2, 0));
    // TODO graph.connect( Output(node1, "output"), Input(node2, "input"));
    graph.connect( node1.output(0), node2.input(0));

    // test connection
    //std::vector<int> v;
    //v[1] = 2;

    
}


void GraphTest::testGraphName()
{
    NodeGraph graph("test1");
    CPPUNIT_ASSERT( Name(graph) == "test1" );
}


