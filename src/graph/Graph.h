#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template<typename V, typename E>
class Graph
{
public:
    /// Constructor
    Graph() {
        // reserve some space to avoid resizing vectors
        // when doing a push backs
        m_vertices.reserve(1024);
        m_edges.reserve(1024);
    }

    /// Destructor
    /// a graph is only a container, it owns nothing
    /// creates nothing and deletes nothing
    ~Graph(){}

    /// Add a vertex in the graph
    void addVertex(V *v) {
        const size_t id = m_vertices.size();
        v->m_vid = id;
        m_vertices.push_back(v);
    }

    /// Add an edge in the graph
    /// 
    void addEdge(E *e) { 
        const size_t id = m_edges.size();
        e->m_eid = id;
        e->m_src->m_outgoing.push_back(e);
        e->m_dst->m_incoming.push_back(e);
        m_edges.push_back(e); 
    }

    /// Return true if there is an edge between src and dst
    bool hasEdge(V *src, V *dst) {

        // Exhaustive search on all outgoing edges 
        typename V::OutEdgeIterator it=src->m_outgoing.begin();
        typename V::OutEdgeIterator itend=src->m_outgoing.end();
        for( it; it!=itend; ++it) {
            if((*it)->m_dst==dst)
                return true;
        }
        return false;
    }

    // TODO 
    void removeVertex(V *v){}
    void removeEdge(E *e){}

    const std::vector<V*> &vertices() const {return m_vertices;}
    const std::vector<E*> &edges() const {return m_edges;}

protected:

    std::vector<V*>     m_vertices;
    typedef typename std::vector<V*>::iterator VertexIterator;
    std::vector<E*>     m_edges;    
    typedef typename std::vector<E*>::iterator EdgeIterator;
};

#endif//GRAPH_H
