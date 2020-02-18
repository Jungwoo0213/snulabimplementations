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

    Node* sLink = nullptr;

    int start;
    int end;
    
    int depth;

    Node* forward[MAX_CHAR]{nullptr};
    Node(int start, int end, int depth){
        this->start = start;
        this->end = end;
        this->depth = depth;
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
        int numMatches = 0;
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
            dfs(curNode, numMatches);
            cout << "Found "<< numMatches<<" matches!"<<endl;
        }else {
            cout << "No match at Pattern index " << index << " with " << P[index] << endl;
            return;
        }
    }

    void dfs(Node* curNode, int& numMatches){
        for(int i =0; i<MAX_CHAR;i++){
            if(curNode->forward[i] != nullptr)
                dfs(curNode->forward[i], numMatches);
        }
        if(curNode->sufIndex>=0){
            cout << "found match at "<<curNode->sufIndex<<endl;
            numMatches++;
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
        root = new Node(-1, -1, 0);
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

        int depth = 0;

        while(index < size){
            //make new branch
            if(curNode->forward[int(T[index])] == nullptr){
                //made tail terminal node
                curNode->forward[int(T[index])] = new Node(index, size-1, 0);
                curNode->forward[int(T[index])]->sufIndex = pos;
                return;
            }
            //contracted locus
            contractedNode = curNode;
            //extended locus
            curNode = curNode->forward[int(T[index])];
            int prevIndex = index;

            if(!findEnd(curNode, index, depth)){
                //branch in the middle
                //make new node (head)
                contractedNode->forward[int(T[prevIndex])] = new Node(prevIndex, index-1, 0);
                Node* head = contractedNode->forward[int(T[prevIndex])];
                //new tail
                head->forward[int(T[index])] = new Node(index, size-1, 0);
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
        root = new Node(0, -1, 0);
        root->sLink = root;
        Node *contractedLocus = root;
        Node *extendedLocus = root;
        Node *head = root;
        Node *cNode, *dNode;
        Node *prevNode;
        int depth;

        int pos = 0;

        int betaSize;
        int betaIndex;

        while(pos<size){
            depth = 0;
            prevNode = nullptr;

            #ifdef DEBUG
            cout << "pos: "<<pos<<endl;
            #endif
            ///////////////////
            /// Substep A
            ///////////////////
            if(contractedLocus == root){
                #ifdef DEBUG
                cout << "alpha is empty"<<endl;
                #endif

                cNode = root;

                //calculate beta
                if(head->length()>0){
                    betaSize = head->length()-1;
                    betaIndex = head->start+1;
                } else {
                    betaSize = -1;
                    betaIndex = -1;
                }
            } else {
                #ifdef DEBUG
                cout << "contractedlocus is not root"<<endl;
                #endif

                cNode = contractedLocus->sLink;
                depth = cNode->depth;

                betaSize = head->length();
                betaIndex = head->start;

                if(head == contractedLocus){
                    betaSize = 0;
                }
            }

            #ifdef DEBUG
            cout << "betaSize: "<<betaSize << " betaIndex: "<<betaIndex <<endl;
            cout << "cNode depth: "<<cNode->depth<<endl;
            
            cout << "\n   step B  "<<endl;
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

                while (curSize > 0 && fNode->forward[int(T[curIndex])]!= nullptr && 
                            fNode->forward[int(T[curIndex])]->length() <= curSize)
                {   
                    #ifdef DEBUG
                    cout << "curIndex: " << curIndex << " char: " << T[curIndex]<<endl;
                    cout << "curSize: "<< curSize<<endl;
                    cout << "fnode depth before: "<<fNode->depth<<endl;
                    cout << "fnode start: "<<fNode->start<<endl;
                    #endif

                    fNode = fNode->forward[int(T[curIndex])];
                    curIndex = curIndex + fNode->length();
                    depth = depth + fNode->length();
                    curSize = curSize - fNode->length();
                }

                #ifdef DEBUG
                cout << "cursize after: " << curSize << endl;
                cout << "depth after: " << depth << endl;
                #endif

                assert(curSize>=0);
                if(curSize == 0 ){
                    dNode = fNode;
                } else {
                    //make new nonterminal node
                    Node* cutNode = fNode->forward[int(T[curIndex])];
                    prevNode = fNode;
                    dNode = new Node(curIndex, curIndex+curSize-1, depth+curSize);
                    depth = depth + curSize;
                    fNode->forward[int(T[curIndex])] = dNode;
                    cutNode->start = cutNode->start + curSize;
                    dNode->forward[int(T[cutNode->start])] = cutNode;

                    #ifdef DEBUG
                    cout << "new nonterminal node(step b): " << curIndex << " - " << curIndex + curSize - 1 << endl;
                    cout << "       depth: "<<dNode->depth<<endl;
                    cout << "cutNode start: "<<cutNode->start<<endl;
                    #endif
                }
            }

            #ifdef DEBUG
            cout << "dnode depth: "<<dNode->depth<<endl;
            cout <<"\n  step C "<<endl;
            #endif

            ///////////////////
            /// Substep C
            ///////////////////
            if(head->sLink == nullptr)
                head->sLink = dNode;
            
            //start of gamma
            Node *curNode = dNode;
            int curIndex = pos + curNode->depth;

            int prevIndex = curIndex;
            if(prevNode == nullptr){
                prevNode = curNode;
            }

            while(1){
                #ifdef DEBUG
                cout << "curIndex: " << curIndex << " checking: "<< T[curIndex] << endl;
                cout << "size: "<<size<<endl;
                #endif

                if(curNode->forward[int(T[curIndex])]==nullptr){
                    #ifdef DEBUG
                    cout << "forward nullptr"<<endl;
                    cout << "making new node: "<<curIndex<<" - "<<size-1<<endl;
                    #endif

                    Node *newTail  = new Node(curIndex, size-1, size-curIndex);
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


                #ifdef DEBUG
                cout << "depth before findEnd: "<<depth<<endl;
                cout << "curIndex before findEnd: "<<curIndex<<endl;
                #endif

                if(!findEnd(curNode, curIndex, depth)){
                    contractedLocus = prevNode;
                    extendedLocus = curNode;

                    #ifdef DEBUG
                    cout << "new Node(middle): " << prevIndex << " - " << curIndex - 1 << endl;
                    cout << "       depth: "<<depth<<endl;
                    cout << "tail: " << curIndex << " - " << size - 1 << endl;
                    cout << "extended node start: " << curNode->start + curIndex - prevIndex << endl;
                    #endif

                    //branch in the middle
                    //make new node
                    head = new Node(prevIndex, curIndex-1, depth);
                    contractedLocus->forward[int(T[prevIndex])] = head;

                    //newtail
                    head->forward[int(T[curIndex])] = new Node(curIndex, size-1, size-1-pos);
                    head->forward[int(T[curIndex])]->sufIndex = pos;

                    //add extened node
                    curNode->start = curNode->start +curIndex - prevIndex;
                    head->forward[int(T[curNode->start])] = curNode;

                    break;
                }
            }

            #ifdef DEBUG
            cout << "--------------------" << endl;
            #endif

            //next suffix
            pos++;
        }
    }

    void linearConstruction1(){
        //McCreight's algorithm

        root = new Node(0, -1, 0);
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
            int depth = 0;
            prevNode = nullptr;

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
                depth = cNode->depth;

                betaSize = head->length();
                betaIndex = head->start;

                if(head == contractedLocus){
                    betaSize = 0;
                }
            }

            #ifdef DEBUG
            cout << "betaSize: "<< betaSize << " betaIndex: "<<betaIndex<<endl;
            cout << "cNode depth: "<< cNode->depth<<endl;
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
                    fNode = fNode->forward[int(T[curIndex])];
                    curIndex = curIndex + fNode->length();                    
                    depth = depth + curSize;
                    curSize = curSize - fNode->length();
                }

                #ifdef DEBUG
                //cout << "cursize: "<<curSize << " forward len: "<< fNode->forward[int(T[curIndex])]->length()<<endl;
                #endif

                assert(curSize>=0);
                if(curSize ==0){
                    dNode = fNode;
                } else {
                    //make new nonterminal node
                    Node* cutNode = fNode->forward[int(T[curIndex])];
                    prevNode = fNode;
                    dNode = new Node(curIndex, curIndex+curSize-1, depth+curSize);
                    fNode->forward[int(T[curIndex])] = dNode;
                    cutNode->start = cutNode->start + curSize;
                    dNode->forward[int(T[cutNode->start])] = cutNode;

                    #ifdef DEBUG
                    cout << "new nonterminal node(step b): "<<curIndex<< " - "<<curIndex+curSize-1<<endl;
                    #endif
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
            
            if(cNode != root && betaSize==0)
                curIndex = pos + cNode->depth;

            
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
                        cout << "making new node: "<<curIndex << " - "<<size-1<<endl;
                    #endif

                    Node *newTail = new Node(curIndex, size - 1, size-curIndex);
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

                if(!findEnd(curNode, curIndex, depth)){
                    contractedLocus = prevNode;
                    extendedLocus = curNode;

                    #ifdef DEBUG
                    cout << "new Node(middle): "<<prevIndex<<" - "<<curIndex-1<<endl;
                    cout << "tail: "<<curIndex<<" - "<<size-1<<endl;
                    cout << "extended node start: "<< curNode->start +curIndex - prevIndex<<endl;
                    #endif

                    //branch in the middle
                    //make new node
                    head = new Node(prevIndex, curIndex-1, depth-1);
                    contractedLocus->forward[int(T[prevIndex])] = head;

                    //newtail
                    head->forward[int(T[curIndex])] = new Node(curIndex, size-1, depth+size-curIndex);
                    head->forward[int(T[curIndex])]->sufIndex = pos;

                    //add extened node
                    curNode->start = curNode->start +curIndex - prevIndex;
                    curNode->depth = curNode->depth + curIndex - prevIndex;
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
    bool findEnd(Node* curNode, int& index, int& depth){
        //do not have to compare the first char
        //depth output is correct
        //while index is one value ahead
        index++;
        depth++;
        for(int i= curNode->start+1; i<=curNode->end;i++){
            if(T[i]==T[index]){
                index++;
                depth++;
            }else{
                //branch in the middle
                return false;
            }
        }
        return true;
    }
};