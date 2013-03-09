#ifndef TESTOP
#define TESTOP

#include <string>
#include "NodeDesc.h"

namespace fission {
/// This is the first implementation of a node
/// totally WIP
/// A new node type inherit a NodeDesc
/// It must provide a typename
/// It must be able to return the inputs values description as well
/// as the output values.

class TestOp : public NodeDesc
{
    // Friends
    // Note, it shouldn't have template friend functions
    template<typename T> friend const char * const TypeName();
    template<typename NT> friend inline size_t NbInputs();
    template<typename NT> friend inline size_t NbOutputs();
    template<typename NT> friend inline size_t NbParameters();

public:
    /// Virtual functions defining the node properties
    const char * typeName() const {return TestOp::s_typeName;}
    const NodeInput * inputs() const {return TestOp::s_inputs;}
    const NodeOutput * outputs() const {return s_outputs;}
    const NodeParameter * parameters() const {return NULL;}
    inline size_t nbInputs() const {return TestOp::s_nbInputs;};
    inline size_t nbOutputs() const {return TestOp::s_nbOutputs;};
    inline size_t nbParameters() const {return TestOp::s_nbParams;};

    virtual void registerFunctions(llvm::Linker *);

private:
    static const char * const       s_typeName;
    static const size_t             s_nbInputs = 2;
    static const size_t             s_nbOutputs = 1;
    static const size_t             s_nbParams = 0;
    static const NodeInput          s_inputs[];
    static const NodeOutput         s_outputs[];
    static const NodeParameter      s_params[];
    static const unsigned int       s_version;

    // Compute functions here ! eventually
    // NodeDesc::FunctionTable  *s_funcs;
};

//TypeId Type(const TestOp &) {return 90;}

}; // namespace fission
#endif//TESTOP
