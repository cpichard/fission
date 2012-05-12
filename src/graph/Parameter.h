#ifndef PARAMETER_H
#define PARAMETER_H

#include "ObjectId.h"
#include "ParameterDesc.h"

namespace fission {

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

};

}; // namespace fission
#endif//PARAMETER_H

