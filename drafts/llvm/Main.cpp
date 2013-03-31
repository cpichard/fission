
#include <cstdlib> // EXIT_SUCCESS
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <iostream>

/*
 *  LLVM framework tests
 *
 */
#include "graph/Module.h"
#include "graph/Node.h"
#include "engine/Context.h"
#include "engine/ComputeEngine.h"
#include "engine/JITEngine.h"

#include <llvm/Linker.h>
#include <llvm/Module.h>
using namespace llvm;

int main(int argc, char **argv)
{
    // Creation of a module which contains nodes
    // Ex : fission::createModule("Comp1", "Compositing", fission::ComputeEngine())
    fission::Module module("test1");

    // Module.loadSetup("")
    // Register a bunch of node types in this module
    // At the moment we create the node description using the jit
    // which is obviously a complicated and bad idea
    fission::JITEngine   jit;
    fission::NodeDesc *testOp = jit.loadNodeDescription("nodes/TestOp.cpp");
    fission::NodeDesc *testSource = jit.loadNodeDescription("nodes/TestSource.cpp");
    fission::NodeDesc *testSink = jit.loadNodeDescription("nodes/TestSink.cpp");
    module.registerNodeDesc(testOp);
    module.registerNodeDesc(testSource);
    module.registerNodeDesc(testSink);

    // Create nodes
    fission::Node *node1 = module.createNode("TestSource", "Src1");
    fission::Node *node2 = module.createNode("TestSource", "Src2");
    fission::Node *node3 = module.createNode("TestOp", "Op1");
    fission::Node *node4 = module.createNode("TestOp", "Op2");
    fission::Node *node5 = module.createNode("TestSink", "Sink1");

    // Connect previously created nodes
    module.connect(Output(node1), Input0(node3));
    module.connect(Output(node2), Input1(node3));
    module.connect(Output(node3), Input0(node4));
    module.connect(Output(node1), Input1(node4));
    module.connect(Output(node4), Input0(node5));

    // Run the computation on the sink
    fission::ComputeEngine engine(module, jit);
    fission::Context ctx(32);
    engine.run(*node5, ctx);

    // Change context value and see what happens
    // when we re-run the sink
    ctx.m_first = 0;
    engine.run(*node5, ctx);

    // How do we delete nodes here ?
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;


    return EXIT_SUCCESS;

}

