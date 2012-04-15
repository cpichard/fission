#include "Node.h"

// Name concept
#include "Name.h"
template std::string Name(Node&);

const char * const Node::s_typeName = "Node";

Node::Node(const std::string &name)
: Plug(name)
, m_id(0)
{
    m_incoming.reserve(16);
    m_outgoing.reserve(16);
}

Node::~Node()
{
}

Plug & Node::addInput(const std::string &name, TypeId t)
{
    // The node graph should create the plug
    // as we need an complete array for traversal
    Plug *plug = new Plug(name);
    plug->m_owner = this; 
    // m_owner->registerPlug(plug)
    
    // Connect it to this plug
    m_incoming.push_back(plug);    

    // Return PlugId ??
    return *plug;
}

Plug & Node::addOutput(const std::string &name, TypeId t)
{
    Plug *plug = new Plug(name);
    
    // Connect it to this plug
    m_outgoing.push_back(plug);    

    // Return PlugId ??
    return *plug;
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
