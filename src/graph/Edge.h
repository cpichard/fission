#ifndef EDGE_H
#define EDGE_H

template<typename T> struct Vertex;

template<typename T>
struct Edge
{
    Vertex<T>   *m_src;
    Vertex<T>   *m_dst;
};

#endif//EDGE_H
