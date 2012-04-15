#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

template<typename T>
struct Vertex
{
    std::vector<Edge<T>*> m_outgoing;
    std::vector<Edge<T>*> m_incoming;
};

#endif//VERTEX_H
