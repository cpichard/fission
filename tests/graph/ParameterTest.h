#ifndef PARAMETERTEST_H
#define PARAMETERTEST_H


#include <cppunit/extensions/HelperMacros.h>

class ParameterTest : public CppUnit::TestFixture
{
public:
    ParameterTest();
    CPPUNIT_TEST_SUITE( ParameterTest );
    CPPUNIT_TEST( testCreateParameter );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreateParameter();
};
#endif//PARAMETERTEST_H
