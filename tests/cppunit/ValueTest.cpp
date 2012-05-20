#include "ValueTest.h"
#include "Value.h"
#include "Module.h"
#include "TestOp.h"
#include "TestSource.h"
#include "TestSink.h"
#include "Name.h"
#include "StandardTypes.h"

using namespace fission;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ValueTest );

ValueTest::ValueTest(){}

void ValueTest::setUp()
{}

void ValueTest::tearDown()
{}

void ValueTest::testCreateValue()
{
    // How are we going to use the values in 
    // our program ?


    // Creation of a dummy value, without nothing in it.
    //Value v;
    //v.set<IntType>(0);
    //Value<IntType> v(0);
    Value v(0);

    //Value v(Float(0));
    //Int i(0);
    //Float f(0.2);
    //String g("Test de string");
    //Filename("");
    
    //Array<Float> j(20);
    //Vector<Int>

    //v.set<IntType>(0);
    //v.get<int>()


    //Value* constValue = IntType::create();

    //CPPUNIT_ASSERT(v==0);

    // Assignation of a value
    //v=10;
    //CPPUNIT_ASSERT(v==10);
}

