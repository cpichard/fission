
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
#include "fission.h"

using namespace llvm;

int main(int argc, char **argv)
{
    // TODO : fission::init();
    //        instead of LLVM initialize

    // Creation of a module which contains nodes
    // Ex : fission::createModule("Comp1", "Compositing", fission::ComputeEngine())
    fission::Module module("test1");

    // Register a bunch of node types in this module
    //module.registerNodeDesc(new fission::TestSource());
    //module.registerNodeDesc(new fission::TestOp());
    //module.registerNodeDesc(new fission::TestSink());
    //module.compileNode("src/nodes/TestOp.cpp");
    //module.compileNode("src/nodes/TestSource.cpp");
    //module.compileNode("src/nodes/TestSink.cpp");
    module.registerNodeDesc("TestSource");
    module.registerNodeDesc("TestOp");
    module.registerNodeDesc("TestSink");


    // Create dynamic nodes
    fission::Node *node1 = module.createNode("TestSource", "Src1");
    fission::Node *node2 = module.createNode("TestSource", "Src2");
    fission::Node *node3 = module.createNode("TestOp", "Op1");
    fission::Node *node4 = module.createNode("TestOp", "Op2");
    fission::Node *node5 = module.createNode("TestSink", "Sink1");

    // Connect previously created nodes
    module.connect(Output0(node1), Input0(node3));
    module.connect(Output0(node2), Input1(node3));
    module.connect(Output0(node3), Input0(node4));
    module.connect(Output0(node1), Input1(node4));
    module.connect(Output0(node4), Input0(node5));

    // Run the computation on the sink 
    fission::ComputeEngine engine(module);
    fission::Context ctx(32);
    engine.run(*node5, ctx);

    // Change context value and see what happens
    // when we re-run the sink
    ctx.m_first = 0;
    engine.run(*node5, ctx);


    return EXIT_SUCCESS;

}

