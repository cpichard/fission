#include "ModuleTest.h"
#include "graph/Module.h"
//#include "nodes/TestOp.h"
//#include "nodes/TestSource.h"
//#include "nodes/TestSink.h"
#include "graph/Name.h"
#include "engine/JITEngine.h"

using namespace fission;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ModuleTest );

ModuleTest::ModuleTest()
{
    m_jit=new fission::JITEngine();
    m_testOp = m_jit->loadNodeDescription("nodes/TestOp.cpp");
    m_testSource = m_jit->loadNodeDescription("nodes/TestSource.cpp");
    m_testSink = m_jit->loadNodeDescription("nodes/TestSink.cpp");
}

ModuleTest::~ModuleTest()
{
    delete m_testOp;
    delete m_testSource;
    delete m_testSink;
    delete m_jit;
}

void ModuleTest::setUp()
{
}

void ModuleTest::tearDown()
{
}


void ModuleTest::testCreateNode()
{
    // Build a module of node
    Module module("test1");
    module.registerNodeDesc(m_testSource);

    // Create an non typed node.
    Node *nodeUnknown = module.createNode("unknown", "");

    // This node should not exist
    CPPUNIT_ASSERT(nodeUnknown == NULL);

    Node *nodeTestSource = module.createNode("TestSource", "test1");
    // This node should exist
    CPPUNIT_ASSERT(nodeTestSource != NULL);
    // Not possible with the JIT
    //CPPUNIT_ASSERT(TypeName(nodeTestSource) == TypeName<TestSource>());

    // Test name
    CPPUNIT_ASSERT(Name(*nodeTestSource) == "test1");
    CPPUNIT_ASSERT(Name(nodeTestSource) == "test1");

    CPPUNIT_ASSERT(NbInputs(nodeTestSource) == 0);
}

// TODO
void ModuleTest::testGetNode()
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


void ModuleTest::testConnectNodes()
{
    // Build a new module
    Module module("test1");
    module.registerNodeDesc(m_testSource);
    module.registerNodeDesc(m_testSink);
    module.registerNodeDesc(m_testOp);

    // Create an non typed node.
    Node *node1 = module.createNode("TestSource", "node1");
    Node *node2 = module.createNode("TestSink", "node2");

    // Connect nodes
    //module.connect( node1->output(0), node2->input(0));
    module.connect(Output(node1), Input0(node2));

    int nbVertices = NbInputs(node1)+NbParameters(node1) + 1
                   + NbInputs(node2)+NbParameters(node2) + 1;
    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == nbVertices );


    int nbEdges = NbInputs(node1)+NbParameters(node1) 
                + NbInputs(node2)+NbParameters(node2) 
                + 1;
    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == nbEdges );

    CPPUNIT_ASSERT( Name(Output(node1)) == "Value");
    Node *node3 = module.createNode("TestOp", "node3");

    CPPUNIT_ASSERT( Name(Input0(node3)) == "InValue1");
    CPPUNIT_ASSERT( Name(Input1(node3)) == "InValue2");

    nbVertices = NbInputs(node1) + NbParameters(node1) + 1
               + NbInputs(node2) + NbParameters(node2) + 1
               + NbInputs(node3) + NbParameters(node3) + 1;
    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == nbVertices );


    nbEdges = NbInputs(node1)+NbParameters(node1)
            + NbInputs(node2)+NbParameters(node2)
            + NbInputs(node3)+NbParameters(node3)
            + 1;

    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == nbEdges );

}

void ModuleTest::testFlowGraph()
{
    // Build a new module
    Module module("test1");
    module.registerNodeDesc(m_testSource);
    module.registerNodeDesc(m_testOp);
    module.registerNodeDesc(m_testSink);

    Node *source = module.createNode("TestSource", "node1");
    Node *sink = module.createNode("TestSink", "node2");
    Node *op = module.createNode("TestOp", "node3");

    // source -> op -> sink
    module.connect(Output(source), Input0(op));
    module.connect(Output(op), Input0(sink));

    // Look in the dataflow graph directly
    int nbVertices = NbInputs(source)+NbParameters(source) + 1
                   + NbInputs(sink)+NbParameters(sink) + 1
                   + NbInputs(op)+NbParameters(op) + 1;
    CPPUNIT_ASSERT( module.m_dataFlowGraph.vertices().size() == nbVertices );


    int nbEdges = NbInputs(source)+NbParameters(source) 
                + NbInputs(sink)+NbParameters(sink) 
                + NbInputs(op)+NbParameters(op) 
                + 2; //nbExternalConnections

    CPPUNIT_ASSERT( module.m_dataFlowGraph.edges().size() == nbEdges );

    // Look if all connections are correct
    Plug *outSource = Output(source);

    CPPUNIT_ASSERT(outSource->m_outgoing.size() == 1);

    CPPUNIT_ASSERT( module.m_dataFlowGraph.hasEdge(Input0(op), Output(op)) );
    CPPUNIT_ASSERT( module.m_dataFlowGraph.hasEdge(Output(source), Input0(op)) );
}


void ModuleTest::testGraphName()
{
    Module module("test1");
    CPPUNIT_ASSERT( Name(module) == "test1" );
}


void ModuleTest::testSetParameter()
{
    Module module("test1");

    module.registerNodeDesc(m_testSource);
    module.registerNodeDesc(m_testOp);
    module.registerNodeDesc(m_testSink);
    Node *source = module.createNode("TestSource", "node1");


    // Describe the modification
    //ParameterModification pm;
    //pm.prepare(SetFloatValue, 5.f);
    //pm(SetFloatValue, 5.f);
    //pm(Param0, SetFloatValue, 5.f);
    //pm.modify(Param0(source));
    //pm( Param0(source), SetFloat4Value, 0.f, 0.4f, 0.2f, 0.5f );

    // ex:
    //pm.modify(Param2(source));
    //pm.modify(Param3(source));
    //pm.modify(Param4(source));

    //fission::apply(pm, Parameter0(nodeId));
    //pm.dump();
    // Apply the modification
    //source->apply(Param0(source), pm);
    //ParameterModification::apply(Parameter0(source), pm);
    //Param0(source)->apply(pm);
    float result;
    Param0(source)->evalFloat(result);

    //Param0(source)->apply(pm);
    Param0(source)->setFloat(7.f);

    float val=0;
    Param0(source)->evalFloat(val);
    CPPUNIT_ASSERT(val==7);


    Param1(source)->setString("./myfile.png");
    std::string strresult;
    Param1(source)->evalString(strresult);

    CPPUNIT_ASSERT(strresult == "./myfile.png");
    CPPUNIT_ASSERT(strresult != "./myfile2.png");

}




