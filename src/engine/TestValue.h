#ifndef TESTVALUE
#define TESTVALUE

#include "Node.h"

class TestValue : public Node
{

// Friends
template<typename T>
friend const char * const TypeName();

public:
    TestValue(const std::string &name)
    : Node(name)
    {}
    
    virtual ~TestValue(){}

    virtual const char * typeName() const {return TestValue::s_typeName;} 

private:
    static const char * const s_typeName;
};

//TypeId Type(const TestValue &) {return 90;}

#endif//TESTVALUE
