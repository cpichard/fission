#ifndef TESTSINK
#define TESTSINK

#include <string>
#include "NodeDesc.h"

namespace fission {
/// This is the first implementation of a node
/// totally WIP
/// A new node type inherit a NodeDesc
/// It must provide a typename
/// It must be able to return the inputs values description as well
/// as the output values.

class TestSink : public NodeDesc
{
    // Friends
    // Note, it shouldn't have template friend functions if I want to
    // make plugins !
    template<typename T> friend const char * const TypeName();
    template<typename NT> friend inline size_t NbInputs();
    template<typename NT> friend inline size_t NbOutputs();

public:
    /// Virtual functions defining the node properties
    const char * typeName() const {return TestSink::s_typeName;}
    const NodeDesc::Input * inputs() const {return s_inputs;}
    const NodeDesc::Output * outputs() const {return NULL;}
    inline size_t nbInputs() const {return TestSink::s_nbInputs;};
    inline size_t nbOutputs() const {return TestSink::s_nbOutputs;};

private:
    static const char * const       s_typeName;
    static const size_t             s_nbInputs = 1;
    static const size_t             s_nbOutputs = 0;
    static const NodeDesc::Input    s_inputs[];
    //static const NodeDesc::Output   s_outputs[];
    static const NodeDesc::Param    s_params[];
    static const unsigned int       s_version;

    // Compute functions here ! eventually
    // NodeDesc::FunctionTable  *s_funcs;
};

//TypeId Type(const TestSink &) {return 90;}
}; // namespace fission
#endif//TESTSINK
