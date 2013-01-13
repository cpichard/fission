#include "TestSource.h"
#include "Parameter.h"
#include "StandardTypes.h"

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

// LLVM code directly here
void TestSource::registerFunctions(llvm::Module *) {
//
//    // build a llvm function
//    // Function prototype
//    std::vector<Type*> Doubles(Args.size(),
//                               Type::getDoubleTy(getGlobalContext()));
//    FunctionType *FT = FunctionType::get(Type::getDoubleTy(getGlobalContext()),
//                                           Doubles, false);
//    Function *F = Function::Create(FT, Function::ExternalLinkage, Name, TheModule);
//    if (F->getName() != Name) {
//        // Delete the one we just made and get the existing one.
//        F->eraseFromParent();
//        F = TheModule->getFunction(Name);
//
//        // If F already has a body, reject this.
//        if (!F->empty()) {
//            ErrorF("redefinition of function");
//        return 0;
//        }
//    }
//
//    // Set names for all arguments.
//      unsigned Idx = 0;
//        for (Function::arg_iterator AI = F->arg_begin(); Idx != Args.size();
//               ++AI, ++Idx) {
//                AI->setName(Args[Idx]);
//
//
//    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);

}



//size_t TestSource::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestSource::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}


}; // namespace fission
