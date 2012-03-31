#include "Node.h"

// Name concept
#include "Name.h"
template std::string Name(Node&);


// Connects two nodes
bool connect(Node &src, Node &dst)
{
    // TODO : test compatibility
    // + test cycle
    src.m_outputs.push_back(&dst);
    dst.m_inputs.push_back(&src);

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
