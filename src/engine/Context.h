#ifndef CONTEXT_H
#define CONTEXT_H

// Execution context.
// Defines all the parameters 

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
    size_t m_first;
    size_t m_last;
};

#endif//CONTEXT_H
