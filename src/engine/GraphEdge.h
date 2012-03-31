#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

template <typename T>
class GraphEdge
{
public:
    GraphEdge(T &src, T &dst)
    : m_src(src)
    , m_dst(dst){}
    ~GraphEdge(){}

protected:
    T &m_src;
    T &m_dst;
};

#endif//GRAPHEDGE_H

