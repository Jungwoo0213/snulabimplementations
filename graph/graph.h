#include <vector>

using namespace std;

class node{
public:
    int value;
    vector<int> adj;
};

class graph{
public:
    vector<node> vertexList;
};