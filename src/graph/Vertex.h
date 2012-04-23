#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

/// Basic vertex
/// It only stores the outgoing and incoming links between vertices
/// with vectors
/// A class must inherits from this if needs to store info.

struct Vertex
{
    Vertex() 
    : m_vid(0)
    { 
        m_outgoing.reserve(16);
        m_incoming.reserve(16);
    }
    
    /// Outgoing edges
    std::vector<Edge*> m_outgoing;
    
    /// Incoming edges
    std::vector<Edge*> m_incoming;
    
    // Type definitions for iterator on outgoing and incoming vectors
    typedef std::vector<Edge*>::iterator OutEdgeIterator;
    typedef std::vector<Edge*>::iterator InEdgeIterator;
    
    /// Vertex id in the graph
    /// TODO Double check if we really need m_vid
    size_t m_vid;
};

#endif//VERTEX_H
