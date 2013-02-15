#include <iostream>
#include "ComputeEngine.h"
#include "GraphAlgorithms.h"
#include "Name.h"
#include "Plug.h"
#include "Edge.h"

#include "llvm/LLVMContext.h"
#include "llvm/Module.h"

using namespace fission;




// Compute visitor is only defined 
class ComputeVisitor
{
public:
    ComputeVisitor()
    {}


    void discoverVertex(Plug *v)
    {
        //std::cout << "discovering vertex " << v << std::endl;
    }

    void finishVertex(Plug *v)
    {
        //std::cout << "finishing vertex " << v << std::endl;
        std::cout << "Plug: " << Name(Owner(v)) << ":" <<Name(v) << " is input " << IsInput(v) << std::endl;
    }

    void examineEdge(PlugLink *e)
    {
        //std::cout << "examining edge" << e << std::endl;
    }

    void treeEdge(PlugLink *e)
    {
        //std::cout << "tree edge " << e << std::endl;
        if(Owner(Src<Plug>(e)) == Owner(Dst<Plug>(e))) {
            std::cout << "same owner " << Name(Owner(Src<Plug>(e))) << std::endl;
        } else {
            std::cout << "diff owner " << Name(Owner(Src<Plug>(e))) << " -> " << Name(Owner(Dst<Plug>(e))) << std::endl;
        }
    }

    void backEdge(PlugLink *e)
    {
        //std::cout << "back edge" << e << std::endl;
    }

    void crossEdge(Edge*e)
    {
        //std::cout << "cross edge" << e << std::endl;
    }

    bool endTraversal(){return false;}
    
};

// Constructor
ComputeEngine::ComputeEngine()
{
}

// Destructor
ComputeEngine::~ComputeEngine()
{}


Status ComputeEngine::compute(Module &module, Node &node, const Context &context)
{
    // Build execution graph recursively
    // Its like an ast
    //visitor.visit(node, module.m_llvmModule);
    //BuildASTComputeVisitor visitor(module);
    ComputeVisitor toto;
    DepthFirstSearch(module.m_dataFlowGraph, Input0(&node), toto);

    // Compile it

    // Execute the function on node
    return SUCCESS;
}

