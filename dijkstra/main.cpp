#include <iostream>
#include <vector>
#include <assert.h>

#include "fibHeap.h"
#include "vertex.h"
#include "dijkstra.h"

using namespace std;

int main(){
    graph* G = new graph();
    vertex* s = new vertex('s');
    vertex* t = new vertex('t');
    vertex* x = new vertex('x');
    vertex* y = new vertex('y');
    vertex* z = new vertex('z');

    G->add_vertex(s);
    G->add_vertex(t);
    G->add_vertex(x);
    G->add_vertex(y);
    G->add_vertex(z);

    G->add_edge(s, t, 10);
    G->add_edge(s, y, 5);
    G->add_edge(t, x, 1);
    G->add_edge(t, y, 2);
    G->add_edge(x, z, 4);
    G->add_edge(y, t, 3);
    G->add_edge(y, z, 2);
    G->add_edge(z, s, 7);
    G->add_edge(z, x, 6);

    cout << G->vertices.at(0)->k<<endl;
    cout << G->vertices.at(1)->k<<endl;
    cout << G->vertices.at(2)->k<<endl;
    cout << G->vertices.at(3)->k<<endl;
    cout << G->vertices.at(4)->k<<endl;

    cout << s->num_degree() << endl;

    cout << s->adj.size() << endl;

    cout << s->adj.at(0).first->k << endl;

    cout << G->vertices[0]->adj.size() << endl;

    cout << G->vertices.at(0)->adj.size() << endl;

    cout << G->vertices.at(0)->adj.at(0).second << endl;

    G->dijkstra(s);

    cout<<"t.p = " << t->p->k <<endl;
    cout<<"x.p = " << x->p->k <<endl;
    cout<<"y.p = " << y->p->k <<endl;
    cout<<"z.p = " << z->p->k <<endl;


    return 0;
}