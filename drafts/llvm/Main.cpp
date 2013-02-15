
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
    // TODO :fission::init();

    // LLVM initialize
    InitializeNativeTarget();
    //LLVMContext &llvmContext = getGlobalContext();

    // The llvm module holds all the code (should be in fission module)

    // ??????
    //llvm::IRBuilder<> Builder(llvmContext);

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
    fission::Node *node4 = module.createNode("TestSink", "Sink1");

    // Connect previously created nodes
    module.connect(Output0(node1), Input0(node3));
    module.connect(Output0(node2), Input1(node3));
    module.connect(Output0(node3), Input0(node4));

    // Tell the module the sink is the node to execute
    fission::ComputeEngine engine;
    fission::Context ctx(0);
    //Value *result = engine.compute(Output0(node4)); // buildResult ?
    engine.compute(module, *node4, ctx); // buildResult ?
    //engine.compute(module, *node1, ctx); // buildResult ?

    //std::cout << result->value() << std::endl;

    return EXIT_SUCCESS;

//=======================================================================//
    // Test loading IR code from a file
    llvm::SMDiagnostic Err;
    llvm::Module *Mod = llvm::ParseIRFile("myfunctions.s", Err, llvm::getGlobalContext());
    //Mod->dump();

    // Build a render engine

    std::string ErrStr;
    llvm::ExecutionEngine *ee = llvm::EngineBuilder(Mod).setErrorStr(&ErrStr).create();
//
//
//    // Function pass 
    llvm::FunctionPassManager OurFPM(Mod);
    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    OurFPM.add(new DataLayout(*ee->getDataLayout()));
    // Provide basic AliasAnalysis support for GVN.
    OurFPM.add(createBasicAliasAnalysisPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    OurFPM.add(createInstructionCombiningPass());
    // Reassociate expressions.
    OurFPM.add(createReassociatePass());
    // Eliminate Common SubExpressions.
    OurFPM.add(createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    OurFPM.add(createCFGSimplificationPass());

    //OurFPM.add(createLoopUnrollPass());
    //OurFPM.add(createFunctionInliningPass());

    OurFPM.doInitialization();
//
//
//    // Get the pointer to the generated code and execute it.
//    // This is fission::Module->execute(output0)
    Function* LF = ee->FindFunctionNamed("_Z7executev");

    std::cout << LF << std::endl;

    // Function pass manager Run
    OurFPM.run(*LF);

    Mod->dump();

    // Compile the function and returns a pointer to it
    void *FPtr = ee->getPointerToFunction(LF);
    double (*FP)() = (double (*)())(intptr_t)FPtr;

    std::cout << FP() << std::endl;
//
//    // Assign it to llvm system
//    //std::map<std::string, Value*> NamedValues;
//    //FunctionPassManager *TheFPM;
//    // Compile, jit and execute

    return EXIT_SUCCESS;
}

