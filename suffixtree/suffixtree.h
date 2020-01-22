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
        //constructTree();
        linearConstruction();
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
        ////McCreight's algorithm

        root = new Node(0, -1);
        root->sLink = root;

        Node *curNode = root;
        Node *contractedNode = root;
        Node *extendedNode = root;
        Node* head = root;

        Node *cNode, *dNode;

        int pos = 0;
        int betaSize = 0;
        int betaIndex = 0;

        

        while (pos < size)
        {   
            #ifdef DEBUG
            cout << "pos: "<<pos<<endl;
            #endif
            ///////////////////
            /// Substep A
            //////////////////
            cNode = contractedNode->sLink;
            betaSize = head->length();
            betaIndex = head->start;

            if(cNode->length() == 0 ){
                betaSize--;
                betaIndex++;
            }

            #ifdef DEBUG
            cout << "betaSize: "<<betaSize<<" betaIndex: "<<betaIndex<<endl;
            #endif
            ////////////////
            /// Substep B
            ////////////////
            //rescanning beta
            Node *prevNode = cNode;
            int oriBetaSize = betaSize;
            if(betaSize>0){
                
                curNode = cNode->forward[int(T[betaIndex])];

#ifdef DEBUG
                cout << "betaSize>0" << endl;
                cout << "curNode->length(): " << curNode->length() << endl;
                cout << "t: " << T[betaIndex] << endl;
                cout << "curnode start: " << curNode->start << endl;
#endif
                int oriBetaSize = betaSize;
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

                        tempNode->start = tempNode->start + oriBetaSize;
                        dNode->forward[int(T[tempNode->start])] = tempNode;

                        cout <<"tempNode start: "<<tempNode->start<<endl;
                        break;
                    }
                    assert(betaSize>0);
                }
            } else {
                dNode = cNode;
            }
            ////////////////
            /// Substep C
            ////////////////
            head->sLink = dNode;
            //int curIndex = pos + betaIndex + betaSize;
            int curIndex;
            if(dNode != root)
                curIndex = pos + oriBetaSize;
            else
                curIndex = pos+1;
            
            #ifdef DEBUG
            cout << "curIndex: "<<curIndex<<endl;
            #endif
            curNode = dNode;
            prevNode = curNode;
            while(curIndex < size){
                cout << "pass"<<endl;
                if(curNode->forward[int(T[curIndex])] == nullptr){
                    #ifdef DEBUG
                    cout << "no forward!"<<endl;
                    cout << "curIndex: "<<curIndex<<endl;
                    #endif
                    //made tail terminal node
                    curNode->forward[int(T[curIndex])] = new Node(curIndex, size - 1);
                    curNode->forward[int(T[curIndex])]->sufIndex = pos;
                    head = curNode;
                    contractedNode = prevNode;
                    extendedNode = curNode;
                    break;
                }
                #ifdef DEBUG
                cout << "found"<<endl;
                #endif

                int prevIndex = curIndex;
                prevNode = curNode;
                curNode = curNode->forward[int(T[curIndex])];

                if(!findEnd(curNode, curIndex)){
                    #ifdef DEBUG
                    cout << "could not find end"<<endl;
                    #endif

                    contractedNode = prevNode;
                    extendedNode = curNode;

                    //branch in the middle
                    //make new node (head)
                    contractedNode->forward[int(T[prevIndex])] = new Node(prevIndex, curIndex-1);
                    head = contractedNode->forward[int(T[prevIndex])];

                    //new tail
                    head->forward[int(T[curIndex])] = new Node(curIndex, size-1);
                    head->forward[int(T[curIndex])]->sufIndex = pos;

                    //add extended node
                    curNode->start = curNode->start + curIndex - prevIndex;
                    head->forward[int(T[curNode->start])] = curNode;

                    #ifdef DEBUG
                    cout << "prevIndex: " << prevIndex << " curIndex: " <<curIndex << endl;
                    cout << "curNode start: "<<curNode->start<<endl;
                    #endif

                    break;
                }
            }

            #ifdef DEBUG
            cout << "----------------"<<endl;
            #endif

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