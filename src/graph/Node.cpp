#include "Node.h"
#include "NodeDesc.h"
#include "Name.h"
#include <iostream>

namespace fission {
template<> const char * const TypeName(Node *);

/// Constructor
Node::Node(const std::string &name, const NodeDesc *type)
: ObjectId<NodeDesc>(name, type)
, m_owner(NULL)
{
    // NOTE: May be a buildFromDescription function could
    // be relevant
    //auto a = [] () {std::cout << "Prout" << std::endl;}

    // FIX ME, add a type for module
    if(type==NULL)
        return;

    Plug *plug=0;
    // Look for inputs and outputs of type
    // and create dynamic plugs from description
    const size_t nbInputs = NbInputs(type);
    //std::cout << "nb inputs for " << name << " " << nbInputs << std::endl;
    const NodeDesc::Input *inputs = Inputs(type);
    for (size_t i=0; i < nbInputs; i++) {
        // TODO Find correct plugtype from name.... 
        // or just use a pointer...
        plug = new Plug(inputs[i].m_name, &PlugInputType, inputs[i].m_type); // TODO correct type
        plug->m_owner = this;
        m_inputPlugs.push_back(plug);
    }

    const NodeDesc::Output *output = Output(type);
    // Find correct plugtype
    m_outputPlugs = new Plug(output->m_name, &PlugOutputType, output->m_type); // TODO correct type
    m_outputPlugs->m_owner = this;

    const size_t nbParams = NbParameters(type);
    const NodeDesc::Param *params = Parameters(type);
    for (size_t i=0; i < nbParams; i++) {
        // TODO : size() might count the number of values, it is not efficient
        Parameter *param = new Parameter(params[i].m_name, params[i].m_type);
        param->m_owner = this;
        m_parameterPlugs.push_back(param);

    }
}


//void Node::apply(Parameter *param, const ParameterModification &pm)
//{
//    //std::cout << "Node::apply" << std::endl;
//    pm.dump();
//    //param->apply(pm);
//}


}; // namespace fission
