#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii; // weight, to

class graph{
    vector<vector<pii>> vecList;

    int dijkstra(int source, int target){
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        vector<int> dist(vecList.size(), INT32_MAX);
        
        pq.push(make_pair(0, source));
        dist[source] = 0;
        
        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for (auto it = vecList[u].begin(); it!=vecList[u].end(); it++){
                int v = it->first;
                int weight = it->second;

                if(dist[v] >dist[u]+weight){
                    dist[v] = dist[u]+weight;
                    pq.push(make_pair(dist[v], v));
                }
            }

        }

        return INT32_MAX;
    }


};