#include <iostream>
#include <string>
#include <assert.h>
#include <queue>

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
        //final char
        //this->T.push_back(3);
        this->T.push_back('#');
        this->size = this->T.length();
        cout<< "Text size: "<<size<<endl;
        //constructTree();
        linearConstruction2();
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

    void print(){
        queue<Node*> Q;
        Q.push(root);
        Node* curNode;
        while(!Q.empty()){
            curNode = Q.front();
            Q.pop();
            for(int i=curNode->start; i<=curNode->end; i++){
                cout << T[i];
            }
            cout <<endl;
            if(curNode->sufIndex<0){
                for(int i=0; i<MAX_CHAR; i++){
                    if(curNode->forward[i] != nullptr)
                        Q.push(curNode->forward[i]);
                }
            }
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
    void linearConstruction2(){
        //McCreight's algorithm

        root = new Node(0, -1);
        root->sLink = root;

        Node *contractedLocus = root;
        Node *extendedLocus = root;
        Node *head = root;

        Node *cNode, *dNode;
        Node *prevNode = nullptr;

        int pos = 0;

        int betaSize;
        int betaIndex;

        while(pos<size){
            #ifdef DEBUG
            cout << "pos: "<<pos<<endl;
            #endif
            ///////////////////
            /// Substep A
            ///////////////////
            if(contractedLocus == root){
                #ifdef DEBUG
                cout<< "alpha is empty"<<endl;
                #endif

                //alpha empty
                cNode = root;
                //calculate beta
                if(head->length()>0){
                    betaSize = head->length()-1;
                    betaIndex = head->start+1;
                } else {
                    betaSize = -1;
                    betaIndex = -1;
                }
            }else{
                #ifdef DEBUG
                cout << "contractedlocus is not root"<<endl;
                #endif

                cNode = contractedLocus->sLink;



                betaSize = head->length();
                betaIndex = head->start;
            }

            #ifdef DEBUG
            cout << "betaSize: "<< betaSize << " betaIndex: "<<betaIndex<<endl;
            #endif

            ///////////////////
            /// Substep B
            ///////////////////
            if(betaSize<=0){
                dNode = cNode;
            } else {
                int curIndex = betaIndex;
                int curSize = betaSize;
                Node *fNode = cNode;
                while(curSize>0 && fNode->forward[int(T[curIndex])]->length()<=curSize){
                    cout << "curSize: "<<curSize<<endl;
                    fNode = fNode->forward[int(T[curIndex])];
                    curIndex = curIndex + fNode->length();
                    curSize = curSize - fNode->length();
                    cout << "curSize after: "<<curSize <<endl;
                    cout << "curIndex: "<<curIndex<<endl;
                }
                cout << "hi"<<endl;

                assert(curSize>=0);
                if(curSize ==0){
                    dNode = fNode;
                } else {
                    //make new nonterminal node
                    Node* cutNode = fNode->forward[int(T[curIndex])];
                    prevNode = fNode;
                    dNode = new Node(curIndex, curIndex+curSize-1);
                    fNode->forward[int(T[curIndex])] = dNode;
                    cutNode->start = cutNode->start + curSize;
                    dNode->forward[int(T[cutNode->start])] = cutNode;
                }
            }

            ///////////////////
            /// Substep C
            ///////////////////
            head->sLink = dNode;
            //start of gamma
            int curIndex;
            if(betaSize>0)
                curIndex = betaIndex + betaSize;
            else
                curIndex = pos;
            
            Node* curNode = dNode;

            int prevIndex = curIndex;
            if(prevNode == nullptr)
                prevNode = curNode;

            while(curIndex<size){
                #ifdef DEBUG
                    cout << "curIndex: "<<curIndex<<endl;
                    cout << "checking: "<<T[curIndex]<<endl;
                #endif

                if(curNode->forward[int(T[curIndex])]==nullptr){
                    #ifdef DEBUG
                        cout << "making new node"<<endl;
                    #endif

                    Node *newTail = new Node(curIndex, size - 1);
                    curNode->forward[int(T[curIndex])] = newTail;
                    newTail->sufIndex = pos;
                    head = curNode;
                    contractedLocus = prevNode;
                    extendedLocus = curNode;
                    break;
                }

                prevNode = curNode;
                curNode = curNode->forward[int(T[curIndex])];
                prevIndex = curIndex;

                if(!findEnd(curNode, curIndex)){
                    contractedLocus = prevNode;
                    extendedLocus = curNode;

                    //branch in the middle
                    //make new node
                    head = new Node(prevIndex, curIndex-1);
                    contractedLocus->forward[int(T[prevIndex])] = head;

                    //newtail
                    head->forward[int(T[curIndex])] = new Node(curIndex, size-1);
                    head->forward[int(T[curIndex])]->sufIndex = pos;

                    //add extened node
                    curNode->start = curNode->start +curIndex - prevIndex;
                    head->forward[int(T[curNode->start])] = curNode;

                    break;
                }
            }

            #ifdef DEBUG
            cout << "--------------------"<<endl;
            #endif

            //next suffix
            pos++;
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