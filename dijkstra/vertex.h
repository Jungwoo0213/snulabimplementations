#ifndef VERTEX_H
#define VERTEX_H

#include <limits>
#include <vector>

using namespace std;

class vertex {
public:
    vertex* p;
    int d;
    char k;
    vector<pair<vertex*, int>> adj;

    vertex(char k){
        p = nullptr;
        d = numeric_limits<int>::max();
        degree = 0;
        this->k = k;
    }
    void insert_edge(vertex* v, int weight){
        pair<vertex*, int> pr ( (vertex*) v, weight);
        v->adj.push_back(pr);
    }
    int num_degree(){return degree;}
    void increment_degree() {degree++;}

private:
    int degree;
};

#endif