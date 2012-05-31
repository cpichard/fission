#ifndef VALUETEST_H
#define VALUETEST_H


#include <cppunit/extensions/HelperMacros.h>

class ValueTest : public CppUnit::TestFixture
{
public:
    ValueTest();
    CPPUNIT_TEST_SUITE( ValueTest );
    CPPUNIT_TEST( testCreateValue );
    CPPUNIT_TEST( testAssignValue );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreateValue();
    void testAssignValue();
};
#endif//VALUETEST_H
