#include <vector>
#include <algorithm>

#include "dijkstra.h"
#include "../fibHeap/fibHeap.h"


void graph::dijkstra(vertex* s){
    initializeSS(s);
    vector<vertex> set;
    fibHeap* Q = new fibHeap();
    vector<vertex>::iterator it;
    for(it=vertices.begin(); it!=vertices.end(); it++){
        Q->insert_vertex( &(*it) );
    }
    while(Q->empty() == false){
        vertex* u = Q->extract_min()->v;
        set.push_back(*u);
        vector<pair<vertex*, int>>::iterator it;
        for(it=u->adj.begin(); it!=u->adj.end(); it++){
            relax(u, (vertex*)it->first, it->second);
        }
    }
}