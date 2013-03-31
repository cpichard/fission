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

Parameter::Parameter(const char *name, size_t id, const BaseType *typ)
: Plug(name, id, &PlugParameterType)
, m_data(NULL)
, m_owner(NULL)
, m_type(typ)
{
    // alloc blind data buffer
    m_data = static_cast<char *>(m_type->alloc());
}

Parameter::~Parameter()
{
    m_type->free(static_cast<void *>(m_data));
    m_data = NULL;
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
    assert(isType<Float>(m_type));
    set(val, m_data);
}
void Parameter::setInt(int val)
{
    assert(isType<Int>(m_type));
    set(val, m_data);
}

void Parameter::setString(const char *val)
{
    assert(isType<String>(m_type));
    *(static_cast<std::string *>((void *)m_data)) = val;
}

void Parameter::evalFloat(float &val)
{
    assert(isType<Float>(m_type));
    eval(val, m_data);
}

void Parameter::evalInt(int &val)
{
    assert(isType<Int>(m_type));
    eval(val, m_data);
}

void Parameter::evalString(std::string &val)
{
    assert(isType<String>(m_type));
    val = *(static_cast<std::string*>((void *)m_data));
}



}; // namespace fission
