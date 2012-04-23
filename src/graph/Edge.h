#ifndef EDGE_H
#define EDGE_H

struct Vertex;

/// Edge implements the idea of a source and a destination
/// with pointers to elements

struct Edge
{
    Edge(Vertex *src, Vertex *dst) 
    : m_src(src)
    , m_dst(dst)
    {}

    /// Source vertex
    Vertex   *m_src;

    /// Destination vertex
    Vertex   *m_dst;

    /// Edge id in the graph
    size_t      m_eid;
};

#endif//EDGE_H
