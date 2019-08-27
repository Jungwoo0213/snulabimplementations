#include <vector>
#include <limits>
#include <assert.h>

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

class graph{
public:
    int numVer;
    int numEdges;
    vector<vertex> vertices;

    void add_vertex(vertex* u){
        vertices.push_back(*u);
        numVer++;
    }
    void add_edge(vertex* u, vertex* v, int weight){
        assert( u != nullptr);
        assert( v != nullptr);
        u->adj.push_back(pair<vertex*, int>(v, weight));

        u->increment_degree();
        numEdges++;
    }
    graph(){
        numEdges = 0;
        numVer = 0;
    }
    void dijkstra(vertex* s);
private:
    void initializeSS(vertex* s){
        vector<vertex>::iterator it;
        for(it = vertices.begin(); it!= vertices.end(); it++){
            it->d = numeric_limits<int>::max();
            it->p = nullptr;
        }
        s->d = 0;
    }
    void relax(vertex* u, vertex* v, int w){
        if(v->d > u->d + w){
            v->d = u->d + w;
            v->p = u;
        }
    }
};