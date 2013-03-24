#ifndef MODULETEST_H
#define MODULETEST_H

#include <cppunit/extensions/HelperMacros.h>

// Forward declaration
namespace fission {
    class JITEngine;
    class NodeDesc;
};

class ModuleTest : public CppUnit::TestFixture
{
public:
    ModuleTest();
    virtual ~ModuleTest(); 
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

private:
    fission::JITEngine   *m_jit;
    fission::NodeDesc    *m_testOp;
    fission::NodeDesc    *m_testSource;
    fission::NodeDesc    *m_testSink;

};
#endif//MODULETEST_H
