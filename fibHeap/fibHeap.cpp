#include "fibHeap.h"
#include <assert.h>
#include <stdlib.h>
#include <cmath>

fnode* fibHeap::insert(int key){
    fnode* x = new fnode(key);
    x->degree = 0;
    x->child = nullptr;
    x->mark = false;
    if (this->min == nullptr){
        insRoot(x);
    } else {
        insRoot(x);
        if (x->key < this->min->key)
            this->min = x;
    }
    num++;
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
    last1->right = root2;
    root2->left = last1;
    root1->left = last2;
    last2->right = root1;
    H->root = root1;
    H->rootNum = H1->rootNum + H2->rootNum;

    if (H1->min == nullptr || (H2->min != nullptr && H2->min->key < H1->min->key))
        H->min = H2->min;
    H->num = H1->num + H2->num;
    return H;
}

fnode* fibHeap::extract_min(){
    fnode* z = this->min;
    if (z != nullptr){
        fnode* x = z->child;
        for (int i=0; i<z->degree; i++){
            insRoot(x);
            x->p = nullptr;
            x->right;
        }
        //remove z from root list
        if(z==root)
            root = z->right;
        z->right->left = z->left;
        z->left->right = z->right;
        this->rootNum--;

        if (this->num == 1) this->min = nullptr;
        else {
            this->min = root;
            consolidate(this);
        }

        this->num--;  
    }

    return z;
}

void fibHeap::consolidate(fibHeap* H){
    double phi = 1.61803;
    int maxDegree = floor(log(H->num)/log(phi));
    fnode* A = new fnode[maxDegree+1];
    for(int i=0; i<maxDegree+2; i++){
        A[i] = nullptr;
    }
    
    
}