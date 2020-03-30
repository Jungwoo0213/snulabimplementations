#include <vector>
#include <stdlib.h>
#include <cstring>
#include <set>

using namespace std;

typedef pair<int, int> pii;

const int MAX = 100000;

vector<pii> list[MAX];
int dis[MAX];

int main(){
    int N, M, i, j, S;

    N = 1000, S = 1;

    memset(dis, 0x7f, sizeof(dis));

    srand(1);
    for (i=1; i<=N; i++){
        for(j=i+1;j<=N; j++){
            list[i].emplace_back(rand()+1, j);
            list[j].emplace_back(rand()+1, i);
        }
    }

    set<pii> active_vertices;
    active_vertices.emplace(0, 0);

    while(!active_vertices.empty()){
        int where = active_vertices.begin()->second;
        
    }

    return 0;
}