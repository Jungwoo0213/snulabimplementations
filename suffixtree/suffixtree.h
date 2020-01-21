#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

const int MAX_CHAR = 256;

class Node{
public:
    //for leaf nodes;
    int sufIndex = -1;

    Node* sLink;

    int start;
    int end;
    Node* forward[MAX_CHAR]{nullptr};
    Node(int start, int end){
        this->start = start;
        this->end = end;
    }
    int length(){
        return end-start+1;
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
        cout<< "Text size: "<<size<<endl;
        constructTree();
    }
    void search(string P){
        unsigned int index = 0;
        Node* curNode = root;
        bool matchFound = false;
        while(index < P.length()){
            if(curNode->forward[int(P[index])] != nullptr){
                curNode = curNode->forward[int(P[index])];
                if (index == P.length() - 1)
                {
                    //match
                    matchFound = true;
                    break;
                }
                index++;
                #ifdef DEBUG
                cout << curNode->start<<" "<<curNode->end<<endl;
                #endif

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
                
                #ifdef DEBUG
                cout << "index: "<<index<<endl;
                #endif

                if(matchFound)
                    //match found
                    break;
            }else {
                cout << "no match: cannot find forward"<<endl;
                //match not found
                break;
            }
        }
        if(matchFound){
            //match found 
            //find terminal nodes by dfs
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
        root->sLink = root;
        for(int i=0; i<size; i++)
            insert(i);
        cout << "Finished construction of suffix tree!"<<endl;
        cout << "--------------------------------------" << endl;
        cout << endl;
    }
    void insert(int index){
        Node* curNode = root;
        Node* contractedNode;
        int pos = index;

        while(index < size){
            //make new branch
            if(curNode->forward[int(T[index])] == nullptr){
                //made tail terminal node
                curNode->forward[int(T[index])] = new Node(index, size-1);
                curNode->forward[int(T[index])]->sufIndex = pos;
                return;
            }
            //contracted locus
            contractedNode = curNode;
            //extended locus
            curNode = curNode->forward[int(T[index])];
            int prevIndex = index;

            if(!findEnd(curNode, index)){
                //branch in the middle
                //make new node (head)
                contractedNode->forward[int(T[prevIndex])] = new Node(prevIndex, index-1);
                Node* head = contractedNode->forward[int(T[prevIndex])];
                //new tail
                head->forward[int(T[index])] = new Node(index, size-1);
                head->forward[int(T[index])]->sufIndex = pos;
                //add extended node
                curNode->start = curNode->start + index-prevIndex;
                head->forward[int(T[curNode->start])] = curNode;
                return;
            }
            //index already increased by findEnd
        }
    }
    void linearConstruction()
    {
        root = new Node(-1, -1);
        root->sLink = root;

        Node *curNode = root;
        Node *contractedNode = root;
        Node *extendedNode;
        Node* head;

        Node *cNode, *dNode;

        int index = 0;
        int pos = index;
        int betaSize = 0;
        int betaIndex = 0;

        while (pos < size)
        {
            ///////////////////
            /// Substep A
            //////////////////
            cNode = contractedNode->sLink;
            if(contractedNode != root){
                betaSize = extendedNode->length();
                betaIndex = extendedNode->start;
            } else {

            }
            ////////////////
            /// Substep B
            ////////////////
            //rescanning beta
            Node *prevNode = cNode;
            curNode = cNode->forward[int(T[betaIndex])];
            while(1){
                if( betaSize > curNode->length()){
                    betaIndex += curNode->length();
                    betaSize -= curNode->length();
                    prevNode = curNode;
                    curNode = curNode->forward[int(T[betaIndex])];
                    assert(curNode!=nullptr);
                } else if(betaSize == curNode->length()) {
                    dNode = curNode;
                    break;
                } else {
                    //make new node
                    dNode = new Node(betaIndex, betaIndex + betaSize - 1);
                    Node *tempNode = prevNode->forward[int(T[betaIndex])];
                    prevNode->forward[int(T[betaIndex])] = dNode;

                    tempNode->start = betaIndex+betaSize;
                    dNode->forward[int(T[betaIndex+betaSize])] = tempNode;
                    break;
                }
                assert(betaSize>0);
            }
            ////////////////
            /// Substep C
            ////////////////
            head->sLink = dNode;
            int curIndex = betaIndex + betaSize;
            curNode = dNode;
            while(curIndex < size){
                if(curNode->forward[int(T[curIndex])] == nullptr){
                    //made tail terminal node
                    curNode->forward[int(T[index])] = new Node(curIndex, size - 1);
                    curNode->forward[int(T[index])]->sufIndex = pos;
                    break;
                }
                int prevIndex = curIndex;
                prevNode = curNode;
                curNode = curNode->forward[int(T[curIndex])];

                if(!findEnd(curNode, curIndex)){
                    contractedNode = prevNode;
                    extendedNode = curNode;

                    //branch in the middle
                    //make new node (head)
                    contractedNode->forward[int(T[prevIndex])] = new Node(prevIndex, curIndex-1);
                    head = contractedNode->forward[int(T[prevIndex])];

                    //new tail
                    head->forward[int(T[index])] = new Node(curIndex, size-1);
                    head->forward[int(T[index])]->sufIndex = pos;

                    //add extended node
                    curNode->start = curNode->start + curIndex - prevIndex;
                    head->forward[int(T[curNode->start])] = curNode;
                }
            }

            //next suffix
            pos++;
        }

        cout << "Finished linear construction of suffix tree!" << endl;
        cout << "--------------------------------------" << endl;
        cout << endl;
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