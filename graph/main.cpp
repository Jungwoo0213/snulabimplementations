#include <iostream>
#include <stdlib.h>

#include "graph.h"
using namespace std;

int main(){
    graph G;
    G.addVertex(1);
    G.addVertex(2);
    G.vertexList[0].addAdj(G.vertexList[1], 4);
    cout << G.vertexList[0].adj[0].second <<endl;

    cout << RAND_MAX<<endl;
    return 0;
}