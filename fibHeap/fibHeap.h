#include <assert.h>
#include <iostream>

#include "../dijkstra/dijkstra.h"

using namespace std;

class fnode{
public:
    int key;
    int degree;
    bool mark;

    fnode* p;
    fnode* child;
    fnode* left;
    fnode* right;

    vertex* v;
    
    fnode(){
        mark = false;
        degree = 0;
        v = nullptr;
    }

    fnode(int key){
        degree = 0;
        mark = false;

        p = child = left = right = nullptr;
        this->key = key;
    }
    fnode(vertex* v){ 
        fnode(v->d);
        this->v = v;
    }
};

class fibHeap {
public:
    int num;
    fnode* root;
    fnode* min;
    int rootNum;
    
    fibHeap(){  
        num = rootNum = 0;
        root = min =  nullptr;
    }
    bool insRoot(fnode* newRoot){
        if(root == nullptr){
            newRoot->left = newRoot->right = newRoot;
            this->root = newRoot;
            this->min = newRoot;
        } else {
            fnode* last = root->left;
            newRoot->left = last->right->left;
            newRoot->right = last->right;
            newRoot->left->right = newRoot;
            newRoot->right->left = newRoot;
        }
        newRoot->p = nullptr;
        rootNum++;
        return true;
    }
    fnode* insert(int key);

    fnode* insert_vertex(vertex* v){
        fnode* x = new fnode(v);
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

    fnode* minimum(){
        return min;
    }

    fnode* extract_min();

    bool empty() const{
        if(num==0)
            return true;
        else
            return false;
        
    }


    fibHeap* join(const fibHeap* H2);
    bool decrease_key(fnode* x, int newKey);
    bool erase(fnode* x);

private:
    void consolidate();
    void fib_heap_link(fnode* y, fnode* x){
        if(y == root) {
            root = y->right;
        }
        assert( root != y );

        //remove from the root list
        y->right->left = y->left;
        y->left->right = y->right;

        //make y child of x
        if (x->child != nullptr){
            fnode* last = x->child->left;
            
            y->right= last->right;
            y->left = last->right->left;
            last->right->left = y;
            last->right = y;
        } else {
            x->child = y;
            y->left = y->right = y;
        }
        
        y->p = x;

        x->degree++;

        y->mark = false;

        rootNum--;
    }

    void cut(fnode* x, fnode* y);
    void cascading_cut(fnode* y);
};
