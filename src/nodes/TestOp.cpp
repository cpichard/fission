
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
#include "llvm/Linker.h"
#include "llvm/Support/IRReader.h"
#include "llvm/Support/SourceMgr.h"

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

void TestOp::registerFunctions(llvm::Linker *linker) {
    llvm::SMDiagnostic Err;
    llvm::Module *mod = llvm::ParseIRFile("TestOp_s.s", Err, llvm::getGlobalContext());

    llvm::Module::FunctionListType &flist = mod->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    (*it).setName("TestOp::execute");
    std::cout << "TestOp : "<< mod << std::endl;

    linker->LinkInModule(mod);
}

}; // namespace fission

