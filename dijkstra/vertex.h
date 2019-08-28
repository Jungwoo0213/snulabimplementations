#ifndef VERTEX_H
#define VERTEX_H

#include <limits>
#include <vector>

#include <iostream>

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
        pair<vertex*, int> pr (v, weight);

        cout << "first: " << pr.first->k << "  second: " << pr.second << endl;

        adj.push_back(pr);

        cout << "adj size: " << adj.size() << endl;

        degree++;
    }
    int num_degree(){return degree;}

private:
    int degree;
};

#endif