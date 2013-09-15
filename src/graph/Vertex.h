#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <cstddef>
#include "Edge.h"

/// Basic implementation of a vertex
/// It only stores the outgoing and incoming links between vertices
/// with vectors
/// A class must inherits from this if needs to store data.
namespace fission {
struct Vertex
{
    Vertex()
    : m_vid(0)
    {
        // NOTE : might be very inefficient when a lot
        // of vertices are created
        m_outgoing.reserve(8);
        m_incoming.reserve(8);
    }

    /// Outgoing edges
    std::vector<Edge*> m_outgoing; // 12

    /// Incoming edges
    std::vector<Edge*> m_incoming; // 12

    // Type definitions for iterator on outgoing and incoming vectors
    typedef std::vector<Edge*>::iterator OutEdgeIterator;
    typedef std::vector<Edge*>::iterator InEdgeIterator;

    /// Vertex id in the graph
    /// TODO Double check if we really need m_vid
    size_t m_vid; // 8
};

inline size_t NbConnectedInputs(const Vertex &v){return v.m_incoming.size();}
inline size_t NbConnectedOutputs(const Vertex &v){return v.m_outgoing.size();}
inline size_t NbConnectedInputs(Vertex *v){return v->m_incoming.size();}
inline size_t NbConnectedOutputs(Vertex *v){return v->m_outgoing.size();}
}; // namespace fission
#endif//VERTEX_H
