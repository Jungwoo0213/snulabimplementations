#include <iostream>
#include <stdlib.h>

#include "graph.h"
using namespace std;

int main(){
    int V = 8;
    graph G(V, true);
    G.addEdge(0, 1, 1);
    G.addEdge(0, 4, 1);
    G.addEdge(1, 5, 1);
    G.addEdge(2, 3, 1);
    G.addEdge(2, 5, 1);
    G.addEdge(2, 6, 1);
    G.addEdge(3, 6, 1);
    G.addEdge(3, 7, 1);
    G.addEdge(5, 6, 1);
    G.addEdge(6, 7, 1);
    

    /* dijkstra test
    int V = 5;
    graph G(V);

    G.addEdge(0, 1, 10);
    G.addEdge(0, 3, 5);
    G.addEdge(1, 2, 1);
    G.addEdge(1, 3, 2);
    G.addEdge(2, 4, 4);
    G.addEdge(3, 1, 3);
    G.addEdge(3, 2, 9);
    G.addEdge(3, 4, 2);
    G.addEdge(4, 0, 7);
    G.addEdge(4, 2, 6);

    for( auto it = G.vecList.begin(); it != G.vecList.end(); it++){
        cout <<it->size()<<" ";
    } cout <<endl;

    //G.dijkstra(0, 1);
    G.print_dijkstra(0);
    */

    return 0;
}