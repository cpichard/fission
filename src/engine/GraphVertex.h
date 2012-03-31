#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

template <typename T>
class GraphVertex
{
    GraphVertex(){}
    ~GraphVertex(){}

protected:
    std::list<GraphEdge<T*>*> m_inputs;
    std::list<GraphEdge<T*>*> m_outputs; 
};

#endif//GRAPHVERTEX_H
