#ifndef TESTVALUE
#define TESTVALUE

#include <string>
#include "NodeType.h"

class TestValue : public NodeType
{
// Friends
template<typename T> friend const char * const TypeName();

public:
    const char * typeName() const {return TestValue::s_typeName;} 
    const NodeType::Input * inputs() const {return s_inputs;}
    const NodeType::Output * outputs() const {return s_outputs;}
    
    inline size_t nbInputs() const; 
    inline size_t nbOutputs() const; 

private:
    static const char * const s_typeName;
    static const NodeType::Input  s_inputs[];
    static const NodeType::Output s_outputs[];
    static const NodeType::Param  s_params[];
    static const unsigned int     s_version;

    // Compute functions here ! eventually
    // NodeType::FunctionTable  *s_funcs;
};

//TypeId Type(const TestValue &) {return 90;}

#endif//TESTVALUE
