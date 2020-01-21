#include <iostream>
#include <string>

using namespace std;

const int MAX_CHAR = 256;

class Node{
public:
    //for leaf nodes;
    int sufIndex = -1;

    int start;
    int end;
    Node* forward[MAX_CHAR]{nullptr};
    Node(int start, int end){
        this->start = start;
        this->end = end;
    }
};

class SuffixTree{
public:
    string T;
    int size;
    Node* root;
    SuffixTree(string T){
        this->T = T;
        this->T.push_back(3);
        this->size = this->T.length();
        constructTree();
    }
    void search(string P){
        int index = 0;
        Node* curNode = root;
        bool matchFound = false;
        while(index < P.length()){
            if(curNode->forward[P[index]] != nullptr){
                curNode = curNode->forward[P[index]];
                if (index == P.length() - 1)
                {
                    //match
                    matchFound = true;
                    break;
                }
                index++;
                cout << curNode->start<<" "<<curNode->end<<endl;
                for(int i= curNode->start+1; i<=curNode->end; i++){
                    if(T[i]==P[index]) {
                        if(index==P.length()-1){
                            //match
                            matchFound = true;
                            break;
                        }
                        index++;
                    }else {
                        //match not found
                        break;
                    }
                }
                cout << "index: "<<index<<endl;
                if(matchFound)
                    //match found
                    break;
            }else {
                //match not found
                break;
            }
        }
        if(matchFound){
            //match found
            dfs(curNode);
        }else {
            cout << "No match at Pattern index " << index << " with " << P[index] << endl;
            return;
        }
    }
    void dfs(Node* curNode){
        for(int i =0; i<MAX_CHAR;i++){
            if(curNode->forward[i] != nullptr)
                dfs(curNode->forward[i]);
        }
        if(curNode->sufIndex>=0){
            cout << "found match at "<<curNode->sufIndex<<endl;
        }
    }
private:
    void constructTree(){
        root = new Node(-1, -1);
        for(int i=0; i<size; i++)
            insert(i);
        cout << "Finished construction of suffix tree!"<<endl;
    }
    void insert(int index){
        Node* curNode = root;
        Node* prevNode = root;
        int pos = index;

        while(index < size){
            //make new branch
            if(curNode->forward[T[index]] == nullptr){
                //made tail terminal node
                curNode->forward[T[index]] = new Node(index, size-1);
                curNode->forward[T[index]]->sufIndex = pos;
                return;
            }
            prevNode = curNode;
            curNode = curNode->forward[T[index]];
            int prevIndex = index;
            if(!findEnd(curNode, index)){
                //branch in the middle
                Node* temp = curNode;
                //make new node
                prevNode->forward[T[prevIndex]] = new Node(prevIndex, index-1);
                //new tail
                prevNode->forward[T[prevIndex]]->forward[T[index]] = new Node(index, size-1);
                prevNode->forward[T[prevIndex]]->forward[T[index]]->sufIndex = pos;
                //add extended node
                curNode->start = curNode->start + index-prevIndex;
                prevNode->forward[T[prevIndex]]->forward[T[curNode->start]] = curNode;
                return;
            }
            index++;
        }
    }
    bool findEnd(Node* curNode, int& index){
        //do not have to compare the first char
        index++;
        for(int i= curNode->start+1; i<=curNode->end;i++){
            if(T[i]==T[index]){
                index++;
            }else{
                //branch in the middle
                return false;
            }
        }
        return true;
    }
};