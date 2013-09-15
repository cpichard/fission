#ifndef CONTEXT_H
#define CONTEXT_H

#include <cstdlib> // size_t
// Execution context.
// Defines all the parameters
namespace fission {

/// Dummy context class, with start and end frames
class Context
{
public:
    Context(size_t frame)
    : m_first(frame)
    , m_last(frame)
    {}

    Context(int first, int last)
    : m_first(first)
    , m_last(last)
    {}

    ~Context(){}

//private:
    int m_first;
    int m_last;
};
}; // namespace fission
#endif//CONTEXT_H
