#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <vector>

template <typename T>
class GraphVertex
{
    friend class NodeGraph;

public:
    GraphVertex()
    : m_owner(NULL)
    {
        // TODO : vector capacity
    }
    ~GraphVertex(){}

protected:
    std::vector<T> m_incoming;
    std::vector<T> m_outgoing; 

    // TODO : is the owner the graph itself ? so it knows how to manage the vertex ?
    T   m_owner; // Owner of the plug
    std::vector<T>  m_owned; // Owned by the plug
    
    // TODO : pointer to the graph
    // TODO : id in the graph ?
};

#endif//GRAPHVERTEX_H
