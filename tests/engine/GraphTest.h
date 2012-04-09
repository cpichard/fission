#ifndef GRAPHTEST_H
#define GRAPHTEST_H


#include <cppunit/extensions/HelperMacros.h>

class GraphTest : public CppUnit::TestFixture
{
public:
    GraphTest();    
    CPPUNIT_TEST_SUITE( GraphTest );
    CPPUNIT_TEST( testCreateNode );
    CPPUNIT_TEST( testGraphName );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreateNode();
    void testGraphName();
    void testGetNode();
    void testConnectNodes();
    
};

#endif//GRAPHTEST_H
