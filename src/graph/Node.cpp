#include "Node.h"
#include "NodeDesc.h"
#include "Name.h"
#include <iostream>

namespace fission {
template<> const char * const TypeName(Node *);

/// Constructor
Node::Node(const std::string &name, size_t id, const NodeDesc *type)
: ObjectId<NodeDesc>(name, id, type)
, m_owner(NULL)
{
    // NOTE: May be a buildFromDescription function could
    // be relevant
    //auto a = [] () {std::cout << "Prout" << std::endl;}

    // FIX ME, add a type for module
    if(type==NULL)
        return;

    // Look for inputs and outputs of type
    // and create dynamic plugs from description
    const size_t nbInputs = NbInputs(type);
    //std::cout << "nb inputs for " << name << " " << nbInputs << std::endl;
    const NodeDesc::Input *inputs = Inputs(type);
    for (size_t i=0; i < nbInputs; i++) {
        // TODO Find correct plugtype from name.... 
        // or just use a pointer...
        const size_t id = m_inputs.size();
        Plug *plug = new Plug(inputs[i].m_name, id, &PlugInputType); // TODO correct type
        plug->m_owner = this;
        m_inputs.push_back(plug);
    }

    const size_t nbOutputs = NbOutputs(type);
    const NodeDesc::Output *outputs = Outputs(type);
    //std::cout << "nb outputs for " << name << " " << nbOutputs << std::endl;
    for (size_t i=0; i < nbOutputs; i++) {
        // Find correct plugtype
        const size_t id = m_outputs.size();
        Plug *plug = new Plug(outputs[i].m_name, id, &PlugOutputType); // TODO correct type
        plug->m_owner = this;
        m_outputs.push_back(plug);
    }

    const size_t nbParams=NbParameters(type);
    const NodeDesc::Param *params = Parameters(type);
    for (size_t i=0; i < nbParams; i++) {
        // Note :
        const size_t id = m_parameters.size();
        Parameter *param = new Parameter(params[i].m_name, id, NULL);
        param->m_owner = this; // TODO : does it need an owner ?
        m_parameters.push_back(param);
        // may be factory of parameter here
        // type.allocParameter()...
        //
    }
}

}; // namespace fission
