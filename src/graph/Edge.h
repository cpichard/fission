#ifndef EDGE_H
#define EDGE_H

namespace fission {
struct Vertex;

/// Edge stores a source, a destination and an Id
/// It doesn't store data.
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
}; // namespace fission
#endif//EDGE_H
