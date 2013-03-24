#include "ValueTest.h"
#include "graph/Module.h"
#include "graph/Name.h"
#include "nodes/TestOp.h"
#include "nodes/TestSink.h"
#include "nodes/TestSource.h"
#include "rtts/StandardTypes.h"
#include "rtts/Value.h"

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
    Value v_int(0);
    CPPUNIT_ASSERT(isType<Int>(v_int));

    Value v_float(0.f);
    CPPUNIT_ASSERT(isType<Float>(v_float));

    //int v=static_cast<int>(v_int);
    Value v_void;
    CPPUNIT_ASSERT(isType<Void>(v_void));
    
    // TODO :
    //int v_int2=2;
    // CPPUNIT_ASSERT(isType<Int>(v_int2));




    // TODO : string and double

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



void ValueTest::testAssignValue()
{
    Value v_int(0);
    v_int = 10;

    CPPUNIT_ASSERT(v_int==10);

}
