#include "TestSink.h"
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


void TestSink::registerFunctions(llvm::Linker *linker) {

    llvm::SMDiagnostic Err;
    llvm::Module *mod = llvm::ParseIRFile("TestSink_s.s", Err, llvm::getGlobalContext());
    llvm::Module::FunctionListType &flist = mod->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    (*it).setName("TestSink::execute");
    std::cout << "TestSink : "<< mod << std::endl;

    linker->LinkInModule(mod);

}



}; // namespace fission
