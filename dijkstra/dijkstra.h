#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <limits>
#include <assert.h>
#include <algorithm>

#include "vertex.h"
#include "fibHeap.h"

using namespace std;

class graph{
public:
    int numVer;
    int numEdges;
    vector<vertex*> vertices;

    graph(){
        numEdges = 0;
        numVer = 0;
    }

    void add_vertex(vertex* u){
        vertices.push_back(u);
        numVer++;
    }
    
    void add_edge(vertex* u, vertex* v, int weight){
        assert( u != nullptr);
        assert( v != nullptr);
        u->insert_edge(v, weight);
        numEdges++;
    }

    void dijkstra(vertex* s){

        initializeSS(s);
        vector<vertex> set;
        fibHeap* Q = new fibHeap();
        vector<vertex*>::iterator it;
        for(it=vertices.begin(); it!=vertices.end(); it++){
            Q->insert_vertex( *it );
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
private:
    void initializeSS(vertex* s){
        vector<vertex*>::iterator it;
        for(it = vertices.begin(); it!= vertices.end(); it++){
            (*it)->d = numeric_limits<int>::max();
            (*it)->p = nullptr;
        }
        s->d = 0;
    }
    void relax(vertex* u, vertex* v, int w){
        if(v->d > u->d + w && u->d != numeric_limits<int>::max()){
            v->d = u->d + w;
            v->p = u;
        }
    }
};

#endif