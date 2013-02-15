#include "TestSink.h"
#include "Parameter.h"
#include "StandardTypes.h"

#include <llvm/Constants.h>
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
//#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"

namespace fission {

// Name of the node type
const char * const TestSink::s_typeName = "TestSink";

/// Version of this node type
const unsigned int TestSink::s_version = 0;

// One inputs for this node
const NodeDesc::Input  TestSink::s_inputs[] = {
    NodeDesc::Input("value", Type<Float>())
};

// No outputs
//const NodeDesc::Output TestSink::s_outputs[]  = {};

// TODO : no parameter
const NodeDesc::Param TestSink::s_params[]   = {};

//extern "C"
//double printd(double X) {
//  printf("result=%f\n", X);
//  return 0;
//}


void TestSink::registerFunctions(llvm::Module *module) {

    std::string funcName("TestSink::execute");

    //
    // Function prototype (Should be in the base class)
    //
//    std::vector<llvm::Type*> argsProto(1, llvm::Type::getDoubleTy(getGlobalContext()));
//    FunctionType *FT = FunctionType::get(
//            llvm::Type::getVoid(getGlobalContext()), // Return type
//            argsProto,                                   // Arguments type
//            false);
//    Function *F = Function::Create(
//            FT,         // Function type 
//            llvm::Function::ExternalLinkage, 
//            funcName, 
//            module);
//    if (F->getName() != funcName) {
//        // Delete the one we just made and get the existing one.
//        F->eraseFromParent();
//        F = module->getFunction(funcName);
//
//        // If F already has a body, reject this.
//        if (!F->empty()) {
//            std::cout << "redefinition of function" << std::endl;
//            return;
//        }
//    }
//
//    // Set names for all arguments.
//    //unsigned Idx = 0;
//    //for (Function::arg_iterator AI = F->arg_begin(); Idx != Args.size(); ++AI, ++Idx) {
//    //    AI->setName(Args[Idx]);
//    //    // Add arguments to variable symbol table.
//    //    //NamedValues[Args[Idx]] = AI;
//    //}
//    Function::arg_iterator arg1 = F->arg_begin();
//    arg1++->setName("val1");
//    arg1->setName("val2");
//    // Insert a basic block in the function
//    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
//    llvm::IRBuilder<> builder(getGlobalContext());
//    builder.SetInsertPoint(BB);
//
//    // TODO : Create allocas
//    llvm::AllocaInst *var1 = builder.CreateAlloca(llvm::Type::getDoubleTy(getGlobalContext()), 0,
//                                    "var1");        
//    llvm::AllocaInst *var2 = builder.CreateAlloca(llvm::Type::getDoubleTy(getGlobalContext()), 0,
//                                    "var2");        
//    //llvm::AllocaInst *res = builder.CreateAlloca(llvm::Type::getDoubleTy(getGlobalContext()), 0,
//    //                               "res");        
//    llvm::Value *L = builder.CreateLoad(var1, "var1");
//    llvm::Value *R = builder.CreateLoad(var2, "var2");
//
//    // TestSource only returns a constant value for the moment
//    //llvm::Value *cst=llvm::ConstantFP::get(getGlobalContext(), llvm::APFloat(2.0)); 
//    llvm::Value *op = builder.CreateFAdd(L, R, "addtmp");
//    llvm::Value *result = builder.CreateStore(op, res);
//    // create return value ?
//    builder.CreateRet(op);
//
//    llvm::verifyFunction(*F);

}


}; // namespace fission
