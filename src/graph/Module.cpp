#include "Module.h"
#include "Name.h"
#include "Type.h"
#include "engine/NodeCompiler.h"

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
    m_nodeCompiler = new NodeCompiler();
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

void Module::compileNode(const char *fileName)
{
    m_nodeCompiler->compile(fileName, m_llvmLinker);

    // TODO :register it
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
