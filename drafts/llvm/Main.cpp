
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



#include "Module.h"

using namespace llvm;

int main(int argc, char **argv)
{
    // LLVM initialize
    InitializeNativeTarget();
    LLVMContext &llvmContext = getGlobalContext();

    // The llvm module holds all the code
    llvm::Module *TheModule = new llvm::Module("My function", llvmContext);


    // ??????
    llvm::IRBuilder<> Builder(llvmContext);

    // Load a graph of code
    //fission::Module module("test1");
    //module.registerNodeDesc(new fission::TestSource());
    //fission::Node *node1 = module.createNode("unknown", "");
    //fission::Node *node2 = module.createNode("unknown", "");
    //module.connect(Output0(node1), Input0(node2));

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
    //void *FPtr = TheExecutionEngine->getPointerToFunction(LF);
    //double (*FP)() = (double (*)())(intptr_t)FPtr;

    // Assign it to llvm system
    //std::map<std::string, Value*> NamedValues;
    //FunctionPassManager *TheFPM;
    // Compile, jit and execute

    

    
    return EXIT_SUCCESS;
}

