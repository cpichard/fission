#ifndef NODECOMPILER_H
#define NODECOMPILER_H

namespace llvm {
class Linker;
};

namespace fission {
class NodeCompiler
{
public:
    NodeCompiler();
    ~NodeCompiler();
    void compile(const char *fileName, llvm::Linker *llvmLinker);
};

};//namespace fission

#endif//NODECOMPILER_H
