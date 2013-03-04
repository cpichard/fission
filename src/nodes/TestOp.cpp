
#include <iostream>

#include "TestOp.h"
#include "Parameter.h"
#include "Status.h"
#include "StandardTypes.h"
#include "Value.h"
// LLVM
#include <llvm/Constants.h>
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"

namespace fission {

/// Name of the node
const char * const TestOp::s_typeName = "TestOp";

/// Version of the node
const unsigned int TestOp::s_version = 0;

// One input for this node
const NodeDesc::Input  TestOp::s_inputs[] = {
    NodeDesc::Input("InValue1", Type<Float>()),
    NodeDesc::Input("InValue2", Type<Float>()),
};

// Only one output, the value of the parameter
const NodeDesc::Output TestOp::s_outputs[] = {
    // TEST
    NodeDesc::Output("OutValue", Type<Float>())
};

// TODO : no parameter
const NodeDesc::Param TestOp::s_params[] = {};

// First test function
Status execute(const Value *in, Value &out) {
    // Do something really cool !
    out = in[0];

    return SUCCESS;
}

using llvm::getGlobalContext;
using llvm::Function;
using llvm::FunctionType;
using llvm::BasicBlock;

void TestOp::registerFunctions(llvm::Module *module) {

    std::string funcName("TestOp::execute");

    //
    // Function prototype (Should be in the base class)
    //
    std::vector<llvm::Type*> argsProto(2, llvm::Type::getDoubleTy(getGlobalContext()));
    FunctionType *FT = FunctionType::get(
            llvm::Type::getDoubleTy(getGlobalContext()), // Return type
            argsProto,                                   // Arguments type
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
    Function::arg_iterator arg1 = F->arg_begin();
    arg1++->setName("var1");
    arg1->setName("var2");

    // Insert a basic block in the function
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    llvm::IRBuilder<> builder(getGlobalContext());
    builder.SetInsertPoint(BB);

    // Create allocas
    llvm::AllocaInst *var1 = builder.CreateAlloca(llvm::Type::getDoubleTy(getGlobalContext()), 0,
                                    "var1");        
    llvm::AllocaInst *var2 = builder.CreateAlloca(llvm::Type::getDoubleTy(getGlobalContext()), 0,
                                    "var2");        

    arg1 = F->arg_begin();
    // Store args in allocas
    builder.CreateStore(arg1++, var1);
    builder.CreateStore(arg1, var2);

    // Load allocas
    llvm::Value *L = builder.CreateLoad(var1, "var1");
    llvm::Value *R = builder.CreateLoad(var2, "var2");

    // TestSource only returns a constant value for the moment
    llvm::Value *op = builder.CreateFAdd(L, R, "addtmp");
    builder.CreateRet(op);

    llvm::verifyFunction(*F);
}

}; // namespace fission

