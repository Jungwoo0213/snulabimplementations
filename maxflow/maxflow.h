#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class maxflow{
public:
    vector<vector<int>> G;
    int n;
    maxflow(vector<vector<int>> &G, int n){
        this->G = G;
        this->n = n;
    }
    int ford_fulkerson(int src, int trg){
        vector<vector<int>> rGraph(G);
        
        vector<int> parent(n, -1);
        int max_flow = 0;

        int u, v;

        while(bfs(rGraph, src,trg, parent)){
            int path_flow = 0x3f3f3f3f;
            for(v=trg; v!=src; v=parent[v]){
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for(v=trg; v!=src; v=parent[v]){
                u=parent[v];
                rGraph[u][v] -=path_flow;
                rGraph[v][u] +=path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }
private:
    bool bfs(vector<vector<int>> rGraph, int src, int trg, vector<int> &parent){
        vector<bool> visited(n, false);
        queue<int> Q;

        visited[src] = true;
        Q.push(src);

        while(!Q.empty()){
            int u = Q.front(); Q.pop();

            for(int v=0; v<n; v++){
                int vf = rGraph[u][v];
                if(visited[v]==false && rGraph[u][v]>0){
                    Q.push(v);
                    parent[v] = u;
                    visited[v] =true;
                }
            }
        }
        return (visited[trg]==true);
    }
};