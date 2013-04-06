#include "ModuleTest.h"
#include "graph/Module.h"
#include "graph/Name.h"
#include "engine/JITEngine.h"

using namespace fission;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ModuleTest );


fission::JITEngine   *ModuleTest::m_jit=0;
fission::NodeDesc    *ModuleTest::m_testOp=0;
fission::NodeDesc    *ModuleTest::m_testSource=0;
fission::NodeDesc    *ModuleTest::m_testSink=0;
fission::NodeDesc    *ModuleTest::m_testValue=0;

ModuleTest::ModuleTest()
{
    std::cout << "Module test constructor" << std::endl;
    if(m_jit==0){m_jit = new fission::JITEngine();};
    if(m_testOp==0){m_testOp = m_jit->loadNodeDescription("nodes/TestOp.cpp");}
    if(m_testSource==0){m_testSource = m_jit->loadNodeDescription("nodes/TestSource.cpp");}
    if(m_testSink==0){m_testSink = m_jit->loadNodeDescription("nodes/TestSink.cpp");}
    if(m_testValue==0){m_testValue = m_jit->loadNodeDescription("nodes/TestValue.cpp");}
}

ModuleTest::~ModuleTest()
{
    std::cout << "Module Test destructor" << std::endl;
    if(m_testOp){ delete m_testOp; m_testOp=NULL;}
    if(m_testSource) { delete m_testSource; m_testSource=NULL;}
    if(m_testSink) {delete m_testSink;m_testSink=NULL;}
    if(m_testValue) {delete m_testValue;m_testValue=NULL;}
    if(m_jit) {delete m_jit;m_jit=NULL;}
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

    module.registerNodeDesc(m_testValue);
    Node *value = module.createNode("TestValue", "node1");
   
    // Param0 of TestValue is float
    float valsrc=7.f;
    Param0(value)->setFloat(valsrc);

    float val=0;
    Param0(value)->evalFloat(val);
    CPPUNIT_ASSERT(val==valsrc);
    CPPUNIT_ASSERT(Param0(value)->asFloat() == valsrc);

    // Param1 is Int
    int valint=4534;
    Param1(value)->setInt(valint);
    CPPUNIT_ASSERT(valint == Param1(value)->asInt());

    // Param2 is String
    Param2(value)->setString("./myfile.png");
    std::string strresult;
    Param2(value)->evalString(strresult);

    CPPUNIT_ASSERT(strresult == "./myfile.png");
    CPPUNIT_ASSERT(strresult != "./myfile2.png");

    delete value;
}




