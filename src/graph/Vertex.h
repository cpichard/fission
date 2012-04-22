#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

/// Client inherits from this class.
/// It only implements the links between vertices

template<typename T>
struct Vertex
{
    // Keep a trace of incoming and outgoing edges
    std::vector<Edge<T>*> m_outgoing;
    std::vector<Edge<T>*> m_incoming;
    
    /// Type definitions for iterator on outgoing and incoming vectors
    typedef typename std::vector<Edge<T>*>::iterator OutEdgeIterator;
    typedef typename std::vector<Edge<T>*>::iterator InEdgeIterator;
    
    /// Vertex id in the graph
    size_t m_vid;
};

#endif//VERTEX_H
