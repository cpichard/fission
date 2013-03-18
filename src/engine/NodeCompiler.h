#ifndef NODECOMPILER_H
#define NODECOMPILER_H

namespace llvm {
class Linker;
class ExecutionEngine;
};

namespace fission {

class NodeDesc;

class NodeCompiler
{
public:
    NodeCompiler();
    ~NodeCompiler();
    NodeDesc *compile(const char *fileName, llvm::Linker *llvmLinker);

    llvm::ExecutionEngine       *m_engine;
};

};//namespace fission

#endif//NODECOMPILER_H
