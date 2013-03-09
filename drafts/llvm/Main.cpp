
#include <cstdlib> // EXIT_SUCCESS
#include "TestSource.h"
#include "TestOp.h"
#include "TestSink.h"
#include "ComputeEngine.h"
#include "Context.h"

#include "llvm/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/IRReader.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/DataLayout.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/LinkAllPasses.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>

/*
 *  LLVM framework tests
 *
 */

#include "Module.h"

using namespace llvm;

int main(int argc, char **argv)
{
    // TODO : fission::init();
    //        instead of LLVM initialize

    // Creation of a module which contains nodes
    // Ex : fission::createModule("Comp1", "Compositing", fission::ComputeEngine())
    fission::Module module("test1");

    // Register a bunch of node types in this module
    module.registerNodeDesc(new fission::TestSource());
    module.registerNodeDesc(new fission::TestOp());
    module.registerNodeDesc(new fission::TestSink());

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

    // TODO : find a cleaner syntax ex:
    //Value *result = engine.compute(Output0(node4)); // buildResult ?
    //engine.compute(module, *node1, ctx); // buildResult ?
    // Or engine.run(module, node, ctx);

    return EXIT_SUCCESS;

}

