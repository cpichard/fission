#include "TestSource.h"
#include "Parameter.h"
#include "StandardTypes.h"
#include <llvm/Constants.h>
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Linker.h"
#include "llvm/Support/IRReader.h"
#include "llvm/Support/SourceMgr.h"
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
void TestSource::registerFunctions(llvm::Linker *linker) {

//=======================================================================//
    // Test loading IR code from a file
    llvm::SMDiagnostic Err;
    llvm::Module *mod = llvm::ParseIRFile("TestSource_s.s", Err, llvm::getGlobalContext());
    llvm::Module::FunctionListType &flist = mod->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    (*it).setName("TestSource::execute");
    std::cout << "TestSource : "<< mod << std::endl;
    linker->LinkInModule(mod);
}



//size_t TestSource::nbInputs() const {return sizeof(s_inputs)/sizeof(NodeDesc::Input);}
//size_t TestSource::nbOutputs() const {return sizeof(s_outputs)/sizeof(NodeDesc::Output);}


}; // namespace fission
