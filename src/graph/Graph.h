#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template<typename T>
struct Vertex
{
    std::vector<Edge<T>*> m_outgoing;
    std::vector<Edge<T>*> m_incoming;
};

template<typename T>
struct Edge
{
    Vertex<T>   *m_src;
    Vertex<T>   *m_dst;
};

template<typename V, typename E>
class Graph
{
public:
    Graph(){}
    ~Graph(){}

    size_t addVertex(V *v){m_vertices.push_back(v);return m_vertices.size();}
    size_t addEdge(E *e){m_edges.push_back(e); return m_edges.size();}

    void removeVertex(V *v){}
    void removeEdget(E *e){}
protected:

    std::vector<V*>     m_vertices;
    std::vector<E*>     m_edges;    
};

#endif//GRAPH_H
