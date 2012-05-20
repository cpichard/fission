#ifndef MODULETEST_H
#define MODULETEST_H


#include <cppunit/extensions/HelperMacros.h>

class ModuleTest : public CppUnit::TestFixture
{
public:
    ModuleTest();
    CPPUNIT_TEST_SUITE( ModuleTest );
    CPPUNIT_TEST( testCreateNode );
    CPPUNIT_TEST( testGraphName );
    CPPUNIT_TEST( testConnectNodes );
    CPPUNIT_TEST( testFlowGraph );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreateNode();
    void testGraphName();
    void testGetNode();
    void testConnectNodes();
    void testFlowGraph();
};
#endif//MODULETEST_H
