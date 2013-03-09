#ifndef TESTSOURCE
#define TESTSOURCE

#include <string>
#include "NodeDesc.h"
namespace fission {
/// This is the first implementation of a node
/// totally WIP
/// A new node type inherit a NodeDesc
/// It must provide a typename
/// It must be able to return the inputs values description as well
/// as the output values.

class TestSource : public NodeDesc
{

    // Friends
    // Note, it shouldn't have template friend functions
    template<typename T> friend const char * const TypeName();
    template<typename NT> friend inline size_t NbInputs();
    template<typename NT> friend inline size_t NbOutputs();

public:
    /// Virtual functions defining the node properties
    const char * typeName() const {return TestSource::s_typeName;}
    const NodeDesc::Input * inputs() const {return NULL;}
    const NodeDesc::Output * outputs() const {return s_outputs;}
    const NodeDesc::Param * parameters() const {return s_params;}
    inline size_t nbInputs() const {return TestSource::s_nbInputs;};
    inline size_t nbOutputs() const {return TestSource::s_nbOutputs;};
    inline size_t nbParameters() const {return TestSource::s_nbParams;}
    virtual void registerFunctions(llvm::Linker *);

private:
    static const char * const       s_typeName;
    static const size_t             s_nbInputs = 0;
    static const size_t             s_nbOutputs = 1;
    static const size_t             s_nbParams = 1;
    static const NodeDesc::Input    s_inputs[];
    static const NodeDesc::Output   s_outputs[];
    static const NodeDesc::Param    s_params[];
    static const unsigned int       s_version;

    // Compute functions here ! eventually
    // NodeDesc::FunctionTable  *s_funcs;
};

//TypeId Type(const TestSource &) {return 90;}
}; // namespace fission
#endif//TESTSOURCE
