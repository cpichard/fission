#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

/// Graph algorithms.
/// At the moment only depth first search is implemented.
/// It's not optimized at all.


#include <algorithm>
#include "Graph.h"

namespace fission {

// Traversal tag
typedef enum {
    WHITE=0, // Not visited
    GRAY,    // Discovered
    BLACK    // Visited
} VertexColor;


/// TraversalStackElement
/// Structure used to simulate a recursive stack when traversing a dag.
/// It stores an element of the stack 
template<typename V, typename E>
struct TraversalStackElement {

    typedef typename V::InEdgeIterator EdgeIt;

    TraversalStackElement(V *v)
    : m_it(v->m_outgoing.begin())
    , m_itEnd(v->m_outgoing.end())
    , m_v(v){}

    // Loads of operator to simplify the code
    inline operator EdgeIt & (){return m_it;}
    inline operator V * (){return m_v;}
    inline operator E *(){return *m_it;}

    inline operator size_t () {return m_v->m_vid;}
    inline operator bool() {return m_it!=m_itEnd;}
    inline TraversalStackElement<V,E> & operator ++ (){++m_it;return *this;}

    // TODO or m_src depending on the traversal direction
    V * nextVertex(){return (*m_it)->m_dst;}

    // The actual datas
    EdgeIt          m_it;
    EdgeIt          m_itEnd;
    V               *m_v;
};

// TODO : preOrder and postOrder visits

template<typename V, typename E, typename Visitor>
void DepthFirstSearch(Graph<V,E> &graph, V *v, Visitor &visitor) {

    // Allocate a color stack to flag the vertices during the traversal
    std::vector<VertexColor> colors(graph.nbVertices());

    // Change color of all nodes to white, means not discovered.
    std::fill(colors.begin(), colors.end(), WHITE);

    // A stack for visiting nodes, ATM a deque is used, might be changed
    typedef TraversalStackElement<V, E>  TSE;
    std::deque<TSE>  stack;

    // Push first vertex in the stack
    stack.push_back(TSE(v));
    colors[v->m_vid]=GRAY; // First vertex is not finished

    // The visitor discover this first vertex
    visitor.discoverVertex(v);

    // Begin the search
    while (!stack.empty()) {

        // Get the last element
        TSE cur(stack.back());

        // Remove it from the stack
        stack.pop_back();

        // Now iterate on all incoming edge
        while (cur) {

            // Examine the edge
            visitor.examineEdge(cur);

            // Retrieve next vertex in the traversal
            V *dst = cur.nextVertex();

            // Check if we have already visited this vertex
            VertexColor &dstColor = colors[dst->m_vid];
            if (dstColor==WHITE) { // Not visited !

                // Edge is valid
                visitor.treeEdge(cur);

                // Discover new vertex
                visitor.discoverVertex(dst);

                // Prepare next edge for later processing and
                // store the current status of the traversal
                stack.push_back(++cur);

                // Go further, same as a recursive call
                cur = TSE(dst);

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


// TODO
void DepthFirstVisit(){}
}; // namespace fission
#endif//GRAPHALGORITHMS_H
