#include "ComputeEngine.h"
#include "Name.h"

using namespace fission;
// Constructor
ComputeEngine::ComputeEngine()
{
}

// Destructor
ComputeEngine::~ComputeEngine()
{}


Status ComputeEngine::compute(Node &node, Context &context)
{
    // Build execution graph recursively
    // Its like an ast
    //BuildASTVisitor visitor(module);
    //visitor.visit(node, module.m_llvmModule);

    // Compile it

    // Execute the function on node
    return SUCCESS;
}

