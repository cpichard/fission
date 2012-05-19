#ifndef GRAPHTEST_H
#define GRAPHTEST_H


#include <cppunit/extensions/HelperMacros.h>

class GraphTest : public CppUnit::TestFixture
{
public:
    GraphTest();    
    CPPUNIT_TEST_SUITE(GraphTest);
    CPPUNIT_TEST(testCreateGraph);
    CPPUNIT_TEST(testCycle);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void testCreateGraph();
    void testCycle();
};

#endif//GRAPHTEST_H
