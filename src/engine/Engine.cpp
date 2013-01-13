#include "Engine.h"
#include "Name.h"

using namespace fission;
// Constructor
Engine::Engine()
{
}

// Destructor
Engine::~Engine()
{}



// TODO send back a renderContext, to know the progression of the rendering
// Le rendercontext peut servir d'object qui monitore le calcul en cours.
// a voir plus tard
#include <iostream>
Status Engine::compute_async(Node &node, Context &context)
{
    std::cout   << "Computing node : "
                << Name(node)
                << " from " << context.m_first
                << " to " << context.m_last
                << std::endl;

    // Goes inside the graph and make tasks


    return SUCCESS;
}

Status Engine::compute(Node &node, Context &context)
{
    return SUCCESS;
}

