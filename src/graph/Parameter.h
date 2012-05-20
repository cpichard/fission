#ifndef PARAMETER_H
#define PARAMETER_H

#include "ObjectId.h"
#include "ParameterDesc.h"

namespace fission {

/// Parameter 
/// a parameter has :
/// * a name
/// * an id
/// * a value or an array of values
/// * a property or an array of properties per value
/// A parameter belongs to a node
/// A parameter can set or get its values
/// A parameter add rules to a value, like a range of an int, default value
/// or proper formatting of a filename


struct Parameter : public ObjectId<ParameterDesc> {

    Parameter(const char *name, size_t id, const ParameterDesc *);
    virtual ~Parameter(){}
    // isA()
    // setValue()
    // value()
    // canCast()
    //
    void *m_data; // Pointer to the data

    // TODO 
    // Properties   m_properties;
    void *m_owner;
};

//template<ValueType>
//Status Set(Parameter &param, const ValueType &value){*param.m_data=value;return 0;}


}; // namespace fission
#endif//PARAMETER_H

