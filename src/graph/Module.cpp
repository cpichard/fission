#include "Module.h"
#include "Name.h"
#include "Type.h"

#include <llvm/ADT/STLExtras.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Linker.h>
#include <llvm/Linker.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/Casting.h>

#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Driver/Driver.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/ArgumentsAdjusters.h>
#include "clang/Driver/Compilation.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Driver/Tool.h"
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>

#include <iostream>

namespace fission {

using std::string;

Module::Module(const std::string &name)
: Node(name, 0, NULL) {

    // Init llvm target
    llvm::InitializeNativeTarget();
    // Declate a new llvm module
    // It will store all the "execute" functions of the nodes
    llvm::LLVMContext &llvmContext = llvm::getGlobalContext();
    m_llvmLinker = new llvm::Linker("ModuleLinker", "Compositing", llvmContext, 0);

}


/// Destructor
/// Module is supposed to destroy everything that it owns
Module::~Module() {

    /// Delete node descriptions
    /// Destroy Plugs
    /// Destroy PlugLinks
    /// Destroy Nodes
}



/// Creates a node from a known type
Node * Module::createNode(const std::string &nodeTypeName, const std::string &nodeName)
{
    std::list<NodeDesc*>::iterator it;
    for (it=m_nodeDesc.begin(); it != m_nodeDesc.end(); ++it) {

        // Type name comparison. There surely is a better way of testing types
        if (nodeTypeName.compare(TypeName(*it))==0) {

            // Last Id is equal to the size of the vector
            size_t id = m_nodes.size(); // Hope vector doesn't count the number of values
            Node *node = new Node(nodeName, id, *it);
            // TODO : node.m_owner =
            //node.m_module = this;
            m_nodes.push_back(node);

            // Add all the plugs of this new node to the graph
            const size_t nbInputs = NbInputs(node);
            for (size_t i=0; i<nbInputs; i++) {
                m_dataFlowGraph.addVertex(node->input(i));
            }

            const size_t nbOutputs = NbOutputs(node);
            for (size_t j=0; j<nbOutputs; j++) {

                // Add vertex
                m_dataFlowGraph.addVertex(node->output(j));

                // Connect all imputs to current outputs
                for (size_t i=0; i<nbInputs; i++) {
                    // TODO !!!
                    PlugLink *pl = new PlugLink("", 0, NULL, node->input(i), node->output(j));
                    m_dataFlowGraph.addEdge(pl);
                }
            }

            // TODO : is it useful to return the node ?
            return node;
        }
    }
    return NULL;
}

/// Remove the node from the module ?? the graph ??
/// Actually deletes the node ?
void Module::disposeNode(Node *node) {

}


using clang::driver::Driver;
using llvm::sys::getDefaultTargetTriple;
using clang::driver::Compilation;
using clang::DiagnosticOptions;
using clang::TextDiagnosticPrinter;
using clang::DiagnosticIDs;
using clang::DiagnosticsEngine; 
using clang::driver::JobList;
using clang::driver::Command;
using clang::driver::ArgStringList;
using clang::CompilerInvocation;
using clang::CompilerInstance;
using clang::CodeGenAction;

void Module::compileNode(const char *fileName)
{
    //
    std::cout << "Compiling " << fileName << "\n";

    // Diagnostics
    DiagnosticOptions *diagOpts = new DiagnosticOptions();
    TextDiagnosticPrinter *diagPrinter = new TextDiagnosticPrinter(llvm::errs(), diagOpts);
    DiagnosticIDs *diagIDs = new DiagnosticIDs();
    DiagnosticsEngine Diags(diagIDs, diagOpts, diagPrinter);        
    
    // Driver that contains all clang options like header path, etc.
    Driver drv("clang", getDefaultTargetTriple()
                    , "a.out"
                    , false
                    , Diags); 

    drv.UseStdLib = true;
    drv.CCCIsCXX = true;
    //drv->CCCIsCPP = true;
    // TODO : no path in code !!!
    // it is needed for standard headers like stddef.h
    drv.ResourceDir = "/home/cyril/usr/local/lib/clang/3.2";

    //// Create the compiler invocation
    std::vector<const char *> args;
    args.push_back("-xc++");
    args.push_back("-I/home/cyril/Develop/fission/src");
    args.push_back(fileName);
    const llvm::OwningPtr<Compilation> 
        Compilation(
            drv.BuildCompilation(llvm::makeArrayRef(args)));    

    // Compilation Job to get the correct arguments
    const JobList &Jobs = Compilation->getJobs();
    const Command *Cmd = llvm::cast<Command>(*Jobs.begin());
    const ArgStringList *const CC1Args = &Cmd->getArguments();

    //Driver->PrintActions(*Compilation);

    llvm::OwningPtr<CompilerInvocation> 
                    CI(new CompilerInvocation);
    CompilerInvocation::CreateFromArgs(
        *CI, CC1Args->data() + 1, CC1Args->data() + CC1Args->size(), Diags);
    
    // Create the compiler instance
    CompilerInstance Clang;
    Clang.setInvocation(CI.take());

    // Get ready to report problems
    Clang.createDiagnostics(args.size(), &args[0]);
    if (!Clang.hasDiagnostics())
        return; 
    
    // Emit only llvm code
    llvm::OwningPtr<CodeGenAction> Act(new clang::EmitLLVMOnlyAction());
    Act->setLinkModule(m_llvmLinker->getModule());
    if (!Clang.ExecuteAction(*Act))
    {
        std::cout << "unable to link" << "\n";    
    }

    m_llvmLinker->LinkInModule(Act->takeModule());
    // TODO : register node desc
    // Call a function that generates a new node ?
    //m_nodeDesc.push_back(newType);
    m_llvmLinker->getModule()->dump();
}

void Module::registerNodeDesc(NodeDesc *newType) {

    // Take ownership of this new type
    m_nodeDesc.push_back(newType);
    // Register the execute function of the node in llvm
    //newType->registerFunctions(m_llvmLinker);

    // Link IR code in the module
    llvm::SMDiagnostic Err;
    llvm::Module *mod = llvm::ParseIRFile(newType->getIrFile(), Err, llvm::getGlobalContext());
    // Rename the first function. We test only with 1 function atm
    llvm::Module::FunctionListType &flist = mod->getFunctionList();
    llvm::Module::FunctionListType::iterator it=flist.begin();
    (*it).setName(string(TypeName(newType))+"::execute");
    std::cout << TypeName(newType) << " : " << mod << std::endl;

    m_llvmLinker->LinkInModule(mod);

}

void Module::unregisterNodeDesc(NodeDesc *type) {

    // TODO : remove the execute function from llvm module

    // TODO: look if some nodes still uses this type
    m_nodeDesc.remove(type);
}

void Module::connect(Plug *src, Plug *dst) {

    // Double check we have the plugs here
    if (src==NULL || dst==NULL) {
        return;
    }

    // TODO : Look if this connection already exists
    if(m_dataFlowGraph.hasEdge(src, dst)) {
        return;
    }

    // Create a new pluglink
    // TODO : is it really useful to have a plug link struct ?
    PlugLink *pl = new PlugLink("",0, NULL, src, dst);
    m_dataFlowGraph.addEdge(pl);

    // TODO
    // Test for cycles


}

}; // namespace fission
