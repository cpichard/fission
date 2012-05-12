
#include "Parameter.h"

namespace fission {

Parameter::Parameter(const char *name, size_t id, const ParameterDesc *desc)
: ObjectId<ParameterDesc>(name, id, desc)
, m_data(NULL)
{}


}; // namespace fission
