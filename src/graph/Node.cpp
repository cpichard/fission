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
    // FIX ME, add a type for module
    if(type==NULL)
        return;

    // Look for inputs and outputs of type and create dynamic plugs
    const size_t nbInputs = NbInputs(type);
    std::cout << "nb inputs for " << name << " " << nbInputs << std::endl;
    const NodeDesc::Input *inputs = Inputs(type);
    for (size_t i=0; i < nbInputs; i++) {
        // Find correct plugtype

        // add an input
        addInput(inputs[i].m_name, NULL); // TODO
    }

    const size_t nbOutputs = NbOutputs(type);
    const NodeDesc::Output *outputs = Outputs(type);
    std::cout << "nb outputs for " << name << " " << nbOutputs << std::endl;

    for (size_t i=0; i < nbOutputs; i++) {
        // Find correct plugtype

        // add an input
        addOutput(outputs[i].m_name, NULL); // TODO
    }
}

// TODO add input du meme type que le PlugTypeInfo
//
void Node::addInput(const char *name, PlugType *type)
{
    size_t id = m_inputs.size();
    Plug *plug = new Plug(name, id, type);
    plug->m_owner = this;
    m_inputs.push_back(plug);
}

void Node::addOutput(const char *name, PlugType *type)
{
    size_t id = m_outputs.size();
    Plug *plug = new Plug(name, id, type);
    plug->m_owner = this;
    m_outputs.push_back(plug);
}

void Node::addParameter(const std::string &name)
{}

}; // namespace fission
