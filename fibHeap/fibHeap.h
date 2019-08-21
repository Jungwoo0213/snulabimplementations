#include <assert.h>
#include <iostream>

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
    
    fnode(){
        mark = false;
        degree = 0;
    }

    fnode(int key){
        degree = 0;
        mark = false;

        p = child = left = right = nullptr;
        this->key = key;
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

    fnode* minimum(){
        return min;
    }

    fnode* extract_min();


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
