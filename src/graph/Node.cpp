#include "Node.h"

template<> const char * const TypeName(Node *);

Node::Node(const std::string &name, size_t id, const NodeType *type)
: ObjectId<NodeType>(name, id, type)
, m_owner(NULL) 
{
   // Look for inputs and outputs of type and create dynamic plugs 

}

// TODO add input du meme type que le PlugTypeInfo
//
void Node::addInput(const std::string &name, PlugType *type)
{
    size_t id = m_inputs.size(); 
    Plug *plug = new Plug(name, id, type); 
    m_inputs.push_back(plug);
}

void Node::addOutput(const std::string &name, PlugType *type)
{}

void Node::addParameter(const std::string &name)
{}

void Node::connect(Plug *src, Plug *dst)
{
    if(src==NULL || dst==NULL)
    {
        return;
    }

    // Check if plug are in the same node
    if(src->m_owner == dst->m_owner)
    {
        //
    }
    else
    {
    }
}
