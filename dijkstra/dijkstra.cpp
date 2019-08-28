#include "dijkstra.h"

void graph::add_edge(vertex* u, vertex* v, int weight){
    assert( u != nullptr);
    assert( v != nullptr);
    u->adj.push_back(pair<vertex*, int>(v, weight));

    u->increment_degree();
    numEdges++;
}