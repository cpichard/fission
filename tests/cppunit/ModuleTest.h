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
    CPPUNIT_TEST( testSetParameter );
    CPPUNIT_TEST_SUITE_END();

public:
    void testCreateNode();
    void testGraphName();
    void testGetNode();
    void testConnectNodes();
    void testFlowGraph();
    void testSetParameter();

private:
    static fission::JITEngine   *m_jit;
    static fission::NodeDesc    *m_testOp;
    static fission::NodeDesc    *m_testSource;
    static fission::NodeDesc    *m_testSink;
    static fission::NodeDesc    *m_testValue;

};
#endif//MODULETEST_H
