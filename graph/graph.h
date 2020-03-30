#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> pii; // weight, to

class graph{
public:
    vector<vector<pii>> vecList;

    graph(int V){
        vecList.resize(V);
    }

    vector<int> dijkstra(int source, int target){
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        vector<int> dist(vecList.size(), 0x3f3f3f3f);
        
        pq.push(make_pair(0, source));
        dist[source] = 0;
        
        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for (auto it = vecList[u].begin(); it!=vecList[u].end(); it++){
                int v = it->second;
                int weight = it->first;

                if(dist[v] >dist[u]+weight){
                    dist[v] = dist[u]+weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }
    void print_dijkstra(int source){
        vector<int> temp;

        temp = dijkstra(0, 1);

        cout << "dist: ";
        for(auto it = temp.begin(); it !=temp.end();it++){
            cout << *it << " ";
        }   cout<<endl;
    }
    void addEdge(int src, int trg, int weight){
        vecList[src].push_back(make_pair(weight, trg));
    }
};