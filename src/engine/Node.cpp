#include "Node.h"

// Name concept
#include "Name.h"
template std::string Name(Node&);

const char * const Node::s_typeName = "Node";

Node::Node(const std::string &name)
: Plug(name)
, m_id(0)
{}

Node::~Node(){};

PlugId Node::addInput(const std::string &name, TypeId t)
{
    // Create new plug
    Plug *input = new Plug(name);
    
    // Connect it to this plug
    //m_incoming.push_bask(input);    
}


// Connects two nodes
LinkId connect(Node &src, PlugId psrc, Node &dst, PlugId pdst)
{
    // TODO : test compatibility
    // + test cycle
    src.m_outgoing.push_back(&dst);
    dst.m_incoming.push_back(&src);

    return true;
}

// Disconnect two nodes
bool disconnect(Node &src, Node &dst)
{
   // TODO 
    return false;
}

bool setParameter(Node &node, const std::string &param, std::string value)
{
    // Look for parameter in the node,
    //

    return true;
}
