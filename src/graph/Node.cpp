#include "Node.h"

template<> const char * const TypeName(Node *);

void Node::addInput(const std::string &name)
{}
void Node::addOutput(const std::string &name)
{}
void Node::addParameter(const std::string &name)
{}
void Node::connect(Plug *src, Plug *dst)
{}
