#include "TestSource.h"
#include "Parameter.h"
#include "StandardTypes.h"
#include <llvm/Constants.h>
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"

#include <iostream>

namespace fission {

// Name of the node
const char * const TestSource::s_typeName = "TestSource";

// Version of the
const unsigned int TestSource::s_version = 0;

// No inputs for this node
const NodeInput 
TestSource::s_inputs[] = {};

// Only one output, the value of the parameter
const NodeOutput 
TestSource::s_outputs[] = {
    NodeOutput("Value", Type<Float>()),
};

// TODO : only one parameter
const NodeParameter
TestSource::s_params[] = {
    // TODO ...
    NodeParameter("val", Type<Float>(), "standard"),
};

using llvm::getGlobalContext;
using llvm::Function;
using llvm::FunctionType;
using llvm::BasicBlock;

// LLVM code directly here
void TestSource::registerFunctions(llvm::Module *module) {

//=======================================================================//
    // Test loading IR code from a file
//    llvm::SMDiagnostic Err;
//    llvm::Module *Mod = llvm::ParseIRFile("myfunctions.s", Err, llvm::getGlobalContext());

    std::string funcName("TestSource::execute");

    //
    // Function prototype (Should be in the base class)
    //
    //std::vector<llvm::Type*> argsProto(1, llvm::Type::getDoubleTy(getGlobalContext()));
    std::vector<llvm::Type*> argsProto;
    FunctionType *FT = FunctionType::get(
            llvm::Type::getDoubleTy(getGlobalContext()),
            argsProto, 
            false);
    Function *F = Function::Create(
            FT,         // Function type 
            llvm::Function::ExternalLinkage, 
            funcName, 
            module);
    if (F->getName() != funcName) {
        // Delete the one we just made and get the existing one.
        F->eraseFromParent();
        F = module->getFunction(funcName);

        // If F already has a body, reject this.
        if (!F->empty()) {
            std::cout << "redefinition of function" << std::endl;
            return;
        }
    }

    // Set names for all arguments.
    //unsigned Idx = 0;
    //for (Function::arg_iterator AI = F->arg_begin(); Idx != Args.size(); ++AI, ++Idx) {
    //    AI->setName(Args[Idx]);
    //    // Add arguments to variable symbol table.
    //    //NamedValues[Args[Idx]] = AI;
    //}
    //Function::arg_iterator arg1 = F->arg_begin();
    //arg1->setName("val");

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    llvm::IRBuilder<> builder(getGlobalContext());
    builder.SetInsertPoint(BB);

    // TestSource only returns a constant value for the moment
    llvm::Value *cst=llvm::ConstantFP::get(getGlobalContext(), llvm::APFloat(2.0)); 

    // create return value ?
    builder.CreateRet(cst);

    llvm::verifyFunction(*F);


}



//size_t TestSource::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestSource::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}


}; // namespace fission
