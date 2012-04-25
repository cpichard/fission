#include "GraphTest.h"
#include "GraphAlgorithms.h"
#include "Vertex.h"
#include "Edge.h"
#include "Name.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( GraphTest );

GraphTest::GraphTest(){}

void GraphTest::setUp(){}

void GraphTest::tearDown(){}

void GraphTest::testCreateGraph() {

    Graph<Vertex, Edge> graph;
    Vertex v1, v2;

    graph.addVertex(&v1);    
    CPPUNIT_ASSERT(graph.vertices().size()==1);
    graph.addVertex(&v2);
    CPPUNIT_ASSERT(graph.vertices().size()==2);
   
    CPPUNIT_ASSERT(graph.edges().size()==0);

    Edge e(&v1, &v2);
    CPPUNIT_ASSERT(e.m_dst==&v2);
    CPPUNIT_ASSERT(e.m_src==&v1);
    graph.addEdge(&e);
    CPPUNIT_ASSERT(graph.edges().size()==1);
    CPPUNIT_ASSERT(graph.hasEdge(&v1,&v2)==true);
    CPPUNIT_ASSERT(graph.hasEdge(&v2,&v1)==false);
    
    Vertex v3, v4, v5;     
}

class Visitor
{
public:
    Visitor()
    : m_nbVertex(0)
    {}

    size_t m_nbVertex;

    void discoverVertex(Vertex *v)
    { 
        //std::cout << "discovering vertex " << v << std::endl;    
    }

    void finishVertex(Vertex *v)
    {   
        m_nbVertex++;
        //std::cout << "finishing vertex " << v << std::endl;    
    }
    void examineEdge(Edge *e)
    {
        //std::cout << "examining edge" << e << std::endl;
    }
    void treeEdge(Edge *e)
    {
        //std::cout << "tree edge" << e << std::endl;
    }

    void backEdge(Edge *e)
    {
        //std::cout << "back edge" << e << std::endl;
    }

    void crossEdge(Edge*e)
    {
        //std::cout << "cross edge" << e << std::endl;
    }
        
    bool endTraversal(){return false;}
};

void GraphTest::testCycle()
{
    Graph<Vertex, Edge> graph;
    Vertex v1, v2;

    graph.addVertex(&v1);    
    CPPUNIT_ASSERT(graph.vertices().size()==1);
    graph.addVertex(&v2);
    
    Visitor visitor;
    
    //DepthFirstSearch(graph, &v1, visitor);

    Edge e(&v1, &v2);
    graph.addEdge(&e);

    //DepthFirstSearch(graph, &v2, visitor);
    //DepthFirstSearch(graph, &v1, visitor);
    
    Vertex *varray= new Vertex[500000];
    graph.addVertex(&varray[0]);
    for (int i=0; i<499999; i++) {
        graph.addVertex(&varray[i+1]);
        Edge *e = new Edge(&varray[i], &varray[i+1]);    
        graph.addEdge(e);
     }

    DepthFirstSearch(graph, &varray[0], visitor);
   
    
    CPPUNIT_ASSERT(visitor.m_nbVertex==500000);
}


