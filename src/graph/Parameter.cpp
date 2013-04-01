#include <iostream>
#include <cstdlib>  // malloc
#include "Parameter.h"
#include "StandardTypes.h"

#include <cassert>

namespace fission {

template<typename T1>
inline void set(T1 val, char *data)
{
    VA_ARG_START(data);
        VA_ARG_SET(val, T1);
    VA_ARG_STOP(data);
}

template<typename T1>
inline void eval(T1 &val, char *data)
{
    VA_ARG_START(data);
        VA_ARG_GET(val, T1);
    VA_ARG_STOP(data);
}

Parameter::Parameter(const char *name, const BaseType *valueType)
: Plug(name, &PlugParameterType, valueType)
//, m_value(valueType->newValue())
, m_data(NULL)
{
    // alloc blind data buffer
    m_data = static_cast<char *>(m_valueType->alloc());
}

Parameter::~Parameter()
{
    m_valueType->free(static_cast<void *>(m_data));
    m_data = NULL;
    
    //m_valueType->freeValue(m_value);
}

//void Parameter::apply( const ParameterModification &pm )
//{
//    std::cout << "Parameter::apply" << std::endl;
//    pm.dump();
//    // Switch change of data by type
//    //m_type->apply(pm, m_data);
//
//    std::cout << "Value stored :" << *((int*)m_data) << std::endl;
//}

void Parameter::setFloat(float val)
{
    assert(isType<Float>(m_valueType));
    set(val, m_data);
}
void Parameter::setInt(int val)
{
    assert(isType<Int>(m_valueType));
    set(val, m_data);
}

void Parameter::setString(const char *val)
{
    assert(isType<String>(m_valueType));
    *(static_cast<std::string *>((void *)m_data)) = val;
}

void Parameter::evalFloat(float &val)
{
    assert(isType<Float>(m_valueType));
    eval(val, m_data);
}

void Parameter::evalInt(int &val)
{
    assert(isType<Int>(m_valueType));
    eval(val, m_data);
}

void Parameter::evalString(std::string &val)
{
    assert(isType<String>(m_valueType));
    val = *(static_cast<std::string*>((void *)m_data));
}



}; // namespace fission
