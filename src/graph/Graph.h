#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cstddef>

#include "engine/Status.h"

/// Graph class
/// Template is used if we have different kinds of Vertices or Edge
/// At the moment, one has to inherit Vertex or Edge
namespace fission {

template<typename V, typename E>
class Graph
{
public:
    /// Constructor
    Graph() {
        // reserve some space to avoid resizing vectors
        // when pushing back data
        m_vertices.reserve(1024);
        m_edges.reserve(1024);
    }

    /// Destructor
    /// a graph is only a container, it owns nothing,
    /// creates nothing and deletes nothing
    /// It only stores handles.
    ~Graph(){}

    /// Add a vertex in the graph
    Status addVertex(V *v) {
        // TODO Test if vertex already exists ?

        // New id for this vertex
        const size_t id = m_vertices.size();
        v->m_vid = id; // TODO SetId function
        m_vertices.push_back(v);
        return SUCCESS;
    }

    /// Add an edge in the graph
    ///
    Status addEdge(E *e) {
        const size_t id = m_edges.size();
        e->m_eid = id; // TODO SetId
        e->m_src->m_outgoing.push_back(e);
        e->m_dst->m_incoming.push_back(e);
        m_edges.push_back(e);
        return SUCCESS;
    }

    bool hasVertex(V *v) {
        // TODO correct return 
        return false;
    }

    /// Return true if there is an edge between src and dst
    bool hasEdge(V *src, V *dst) {

        // Exhaustive search on all outgoing edges
        typename V::OutEdgeIterator it=src->m_outgoing.begin();
        typename V::OutEdgeIterator itend=src->m_outgoing.end();
        for (; it!=itend; ++it) {
            if ((*it)->m_dst==dst) {
                return true;
            }
        }
        return false;
    }

    // TODO
    Status removeVertex(V *v){return ERROR;}
    Status removeEdge(E *e){return ERROR;}

    const std::vector<V*> &vertices() const {return m_vertices;}
    const std::vector<E*> &edges() const {return m_edges;}

    size_t nbVertices()const{return m_vertices.size();}
    size_t nbEdges()const{return m_edges.size();}

protected:
    /// Array of vertices
    std::vector<V*>     m_vertices;
    typedef typename std::vector<V*>::iterator VertexIterator;

    /// Array of edges
    std::vector<E*>     m_edges;
    typedef typename std::vector<E*>::iterator EdgeIterator;
};
}; // namespace fission
#endif//GRAPH_H
