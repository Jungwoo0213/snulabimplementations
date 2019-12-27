#include <iostream>
#include <string>

using namespace std;

const int MAX_CHAR = 256;

class Node{
public:
    char c;
    //for leaf nodes;
    int index = -1;
    Node* forward[MAX_CHAR]{nullptr};
    Node(char c){
        this->c = c;
    }
};

class SuffixTree{
public:
    string T;
    int size;
    Node* root;
    SuffixTree(string T){
        this->T = T;
        this->size = T.length();
        constructTree();
    }
    void search(string P){
        int index = 0;
        Node* curNode = root;
        while(index < P.length()){
            if(curNode->forward[P[index]] != nullptr){
                curNode = curNode->forward[P[index]];
            }else {
                cout << "No match at Pattern index "<<index<<" with "<<P[index]<<endl;
                return;
            }
            index++;
        }

        //match found
        dfs(curNode);
    }
    void dfs(Node* curNode){
        for(int i =0; i<MAX_CHAR;i++){
            if(curNode->forward[i] != nullptr)
                dfs(curNode->forward[i]);
        }
        if(curNode->index>=0){
            cout << "found match at "<<curNode->index<<endl;
        }
    }
private:
    void constructTree(){
        root = new Node( 0);
        for(int i=0; i<size; i++)
            insert(i);
    }
    void insert(int index){
        Node* curNode = root;
        int pos = index;
        while(index < size){
            if(curNode->forward[T[index]] == nullptr)
                curNode->forward[T[index]] = new Node(T[index]);
            curNode = curNode->forward[T[index]];
            index++;
        }
        curNode->index = pos;
    }
};