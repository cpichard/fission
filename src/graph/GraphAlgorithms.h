#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include <algorithm>

#include "Graph.h"
typedef enum {
    WHITE=0,
    GRAY,
    BLACK
} VertexColor;

template<typename V, typename E>
struct TraversalFunctionStack {

    typedef typename V::InEdgeIterator EdgeIt;

    TraversalFunctionStack(V *v)
    : m_it(v->m_outgoing.begin())
    , m_itEnd(v->m_outgoing.end())
    , m_v(v){}
    
    inline operator EdgeIt & (){return m_it;}
    inline operator V * (){return m_v;}
    inline operator size_t () {return m_v->m_vid;} 
    inline operator bool() {return m_it!=m_itEnd;}
    inline operator E *(){return *m_it;}
    inline TraversalFunctionStack<V,E> & operator ++ (){++m_it;return *this;}

    EdgeIt          m_it;
    EdgeIt          m_itEnd;
    V               *m_v;
};

// TODO : preOrder and postOrder visits

template<typename V, typename E, typename Visitor>
void DepthFirstSearch(Graph<V,E> &graph, V *v, Visitor &visitor) {
    
    // Allocate a color stack to flag the vertices
    std::vector<VertexColor> colors(graph.nbVertices());

    // Change color to white, double check it's by default
    std::fill(colors.begin(), colors.end(), WHITE);

    // A stack for visiting nodes
    typedef TraversalFunctionStack<V, E>  TFS;
    std::deque<TFS>  stack;

    // Push first vertex in the stack
    stack.push_back(TFS(v));
    colors[v->m_vid]=GRAY;

    // The visitor discover this first vertex
    visitor.discoverVertex(v);

    // Begin the search
    //typename V::InEdgeIterator it;
    //typename V::InEdgeIterator itEnd;
    while (!stack.empty()) {

        // Get the last element
        TFS cur(stack.back());

        // Remove it from the stack
        stack.pop_back();

        // Now iterate on all incoming edge
        while(cur) {

            // Examine the edge
            visitor.examineEdge(cur);
            
            // Retrieve destination vertex
            V *dst = static_cast<E*>(cur)->m_dst;

            // Check if we have already visited this vertex
            VertexColor &dstColor = colors[dst->m_vid]; 
            if(dstColor==WHITE) {
                // Not visited !
                // edge is valid
                visitor.treeEdge(cur);

                // Store the current status of the traversal
                stack.push_back(++cur);
                // And go further
                cur = TFS(dst);
                // Discover new vertex
                visitor.discoverVertex(dst);                     

            } else if (dstColor==GRAY) {
                // This vertex is already planned to be visited
                visitor.backEdge(cur);
                ++cur;
            } else {
                // This vertex has already been visited
                visitor.crossEdge(cur);
                ++cur;
            }
        }

        // Finally visit
        visitor.finishVertex(cur);
        colors[cur] = BLACK;
        if (visitor.endTraversal()) {
            return;
        }
    }
}


void DepthFirstVisit(){}

#endif//GRAPHALGORITHMS_H
