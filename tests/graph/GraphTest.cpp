#include "GraphTest.h"
#include "Module.h"
#include "TestOp.h"
#include "TestSource.h"
#include "TestSink.h"
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
    // Build a module of node
    Module module("test1");
    module.registerNodeDesc(new TestSource());
    
    // Create an non typed node. 
    Node *nodeUnknown = module.createNode("unknown", "");
    
    // This node should not exist 
    CPPUNIT_ASSERT(nodeUnknown == NULL);

    Node *nodeTestSource = module.createNode("TestSource", "test1");
    // This node should exist
    CPPUNIT_ASSERT(nodeTestSource != NULL);
    CPPUNIT_ASSERT(TypeName(nodeTestSource) == TypeName<TestSource>());

    // Test name
    CPPUNIT_ASSERT(Name(*nodeTestSource) == "test1");
    CPPUNIT_ASSERT(Name(nodeTestSource) == "test1");

    CPPUNIT_ASSERT( NbInputs(nodeTestSource) == 0);
    CPPUNIT_ASSERT( NbOutputs(nodeTestSource) == 1);
    CPPUNIT_ASSERT( NbOutputs<TestSource>() == 1);
    CPPUNIT_ASSERT( NbInputs<TestSource>() == 0);
}

// TODO 
void GraphTest::testGetNode()
{
    // Build a module of node
    Module module("test1");
    
    // Create an non typed node. 
    Node *node1 = module.createNode("TestSource", "node1");
    Node *node2 = module.createNode("TestSource", "node2");
    Node *node3 = module.createNode("TestSource", "node3");
    Node *node4 = module.createNode("TestSource", "node4");

    //const std::vector &nodes=Nodes(module);

    // Get nodes of the module
    // std::vector<Node&> nodes = module.getNodeNames()
}


void GraphTest::testConnectNodes()
{
    // Build a new module
    Module module("test1");
    module.registerNodeDesc(new TestSource());
    module.registerNodeDesc(new TestSink());
    module.registerNodeDesc(new TestOp());

    // Create an non typed node. 
    Node *node1 = module.createNode("TestSource", "node1");
    Node *node2 = module.createNode("TestSink", "node2");

    // Connect nodes
    //module.connect( node1->output(0), node2->input(0));
    module.connect(Output0(node1), Input0(node2));

    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == 2 ); 
    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == 1 ); 

    CPPUNIT_ASSERT( Name(Output0(node1)) == "Value");
    
    Node *node3 = module.createNode("TestOp", "node3");
    
    CPPUNIT_ASSERT( Name(Input0(node3))== "InValue");

    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == 4 ); 
    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == 2 ); 

}

void GraphTest::testFlowGraph()
{
    // Build a new module
    Module module("test1");
    module.registerNodeDesc(new TestSource());
    module.registerNodeDesc(new TestSink());
    module.registerNodeDesc(new TestOp());
   

    Node *source = module.createNode("TestSource", "node1");
    Node *sink = module.createNode("TestSink", "node2");
    Node *op = module.createNode("TestOp", "node3");

    // source -> op -> sink
    module.connect(Output0(source), Input0(op));
    module.connect(Output0(op), Input0(sink));
   
    // Look in the dataflow graph directly 
    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == 4 ); 
    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == 3 ); 

    // Look if all connections are correct
    Plug *outSource = Output0(source);

    CPPUNIT_ASSERT(outSource->m_outgoing.size() == 1);
    
    CPPUNIT_ASSERT( module.m_dataFlowGraph.hasEdge(Input0(op), Output0(op)) ); 
    CPPUNIT_ASSERT( module.m_dataFlowGraph.hasEdge(Output0(source), Input0(op)) ); 
}


void GraphTest::testGraphName()
{
    Module module("test1");
    CPPUNIT_ASSERT( Name(module) == "test1" );
}


