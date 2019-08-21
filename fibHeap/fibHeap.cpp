#include "fibHeap.h"
#include <assert.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <limits.h>

using namespace std;

fnode* fibHeap::insert(int key){
    fnode* x = new fnode(key);
    x->degree = 0;
    x->child = nullptr;
    x->mark = false;
    if (min == nullptr){
        insRoot(x);
    } else {
        insRoot(x);
        if (x->key < min->key)
            min = x;
    }
    num++;
    return x;
}

fibHeap* fibHeap::join(const fibHeap* H2){
    fibHeap* H = new fibHeap();
    fibHeap* H1 = this;
    H->min = H1->min;
    fnode* root1 = H1->root;
    fnode* last1 = H1->root->left;
    fnode* root2 = H2->root;
    fnode* last2 = H2->root->left;

    //concatenating the root list of H2 with the root list of H
    if(root1 == nullptr)
        H->root = root2;
    else if (root2 == nullptr){
        H->root = root1;
    } else {
        last1->right = root2;
        root2->left = last1;
        root1->left = last2;
        last2->right = root1;
        H->root = root1;
    }
    H->rootNum = H1->rootNum + H2->rootNum;

    if (H1->min == nullptr || (H2->min != nullptr && H2->min->key < H1->min->key))
        H->min = H2->min;
    H->num = H1->num + H2->num;
    return H;
}

fnode* fibHeap::extract_min(){
    fnode* z = min;

    if (z != nullptr){

        if (z->child != nullptr){
            fnode* x = z->child;
            fnode* xr;
            for (int i=0; i<z->degree; i++){
                xr = x->right;
                insRoot(x);
                x = xr;
            }
        }
        
        //remove z from root list
        if (z->right != z){
            if(z==root)
                root = z->right;
            z->right->left = z->left;
            z->left->right = z->right;
            rootNum--;
        } else {
            root = nullptr;
        }
        
        
        if (num == 1) {
            min = nullptr;
            assert(root==nullptr);
        } else {
            min = root;
            consolidate();
        }

        num--;
    }

    return z;
}

void fibHeap::consolidate(){
    const double phi = 1.61803;
    const int maxDegree = floor(log(num)/log(phi));

    fnode** A = new fnode*[maxDegree+1];
    for(int i=0; i<maxDegree+2; i++){
        A[i] = nullptr;
    }
    fnode* w = root;
    fnode* x;

    int curNum = rootNum;
    
    for(int i=0; i<curNum; i++){
        x = w;
        int d = x->degree;

        while( A[d] != nullptr){
            fnode* y = A[d];
            if (x->key > y->key){
                fnode* tmp = x;
                x = y;
                y = tmp;
                w = x;
            }

            fib_heap_link(y, x);

            A[d] = nullptr;
            d++;
        }
        A[d] = x;

        w = w->right;
    }

    min = nullptr;
    for (int i=0; i<maxDegree+1; i++){
        if(A[i]!= nullptr){
            if(min == nullptr){
                min = A[i];
            } else if (A[i]->key < min->key){
                min = A[i];
            }
        }
    } 
    
    //end of consolidate
}

bool fibHeap::decrease_key(fnode* x, int newKey){
    if (newKey > x->key){
        cerr << "new key is greater than current key" <<endl;
        return false;
    }
    x->key = newKey;
    fnode* y = x->p;

    if(y != nullptr && (x->key < y->key)){
        cut(x, y);
        cascading_cut(y);
    }
    if(x->key < min->key)
        min = x;

    return true;
}

void fibHeap::cut(fnode* x, fnode* y){
    if (y->child == x){
        y->child = x->right;
    }

    if (y->degree==1)
        y->child = nullptr;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
    }
    
    y->degree--;

    insRoot(x);
    x->p = nullptr;
    x->mark = false;
}

void fibHeap::cascading_cut(fnode* y){
    fnode* z = y->p;
    if(z != nullptr){
        if(y->mark == false)
            y->mark =true;
        else{
            cut(y, z);
            cascading_cut(z);
        }
    }
}

bool fibHeap::erase(fnode* x){
    decrease_key(x, INT_MIN);
    extract_min();
    return true;
}