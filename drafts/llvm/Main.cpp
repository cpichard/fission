
#include <cstdlib> // EXIT_SUCCESS
#include "TestSource.h"

#include "llvm/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/DataLayout.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"
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
    LLVMContext &llvmContext = getGlobalContext();

    // The llvm module holds all the code (should be in fission module)

    // ??????
    llvm::IRBuilder<> Builder(llvmContext);

    // Creation of a module which contains nodes
    fission::Module module("test1");
    module.registerNodeDesc(new TestSource());
    module.registerNodeDesc(new TestOp());
    module.registerNodeDesc(new TestSink());
    fission::Node *node1 = module.createNode("TestSource", "");
    fission::Node *node2 = module.createNode("TestSource", "");
    fission::Node *node3 = module.createNode("TestOp", "");
    fission::Node *node4 = module.createNode("TestSink", "");
    module.connect(Output0(node1), Input0(node3));
    module.connect(Output0(node2), Input1(node3));
    module.connect(Output0(node3), Input0(node4));

    // Tell the module the sink is the node to execute
    ExecutionEngine engine(module);
    engine.execute(Output0(module)); // buildResult ?

    // Build a render engine

    std::string ErrStr;
    ExecutionEngine *TheExecutionEngine = EngineBuilder(TheModule).setErrorStr(&ErrStr).create();


    // Function pass 
    FunctionPassManager OurFPM(TheModule);
    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    OurFPM.add(new DataLayout(*TheExecutionEngine->getDataLayout()));
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

    OurFPM.doInitialization();


    // Get the pointer to the generated code and execute it.
    // This is fission::Module->execute(output0)
    //void *FPtr = TheExecutionEngine->getPointerToFunction(LF);
    //double (*FP)() = (double (*)())(intptr_t)FPtr;

    // Assign it to llvm system
    //std::map<std::string, Value*> NamedValues;
    //FunctionPassManager *TheFPM;
    // Compile, jit and execute

    return EXIT_SUCCESS;
}

