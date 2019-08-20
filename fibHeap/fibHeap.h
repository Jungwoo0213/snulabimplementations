#include <assert.h>

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

    }

    fnode(int key){
        degree = 0;
        mark = false;

        p = child = left = right = nullptr;
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
        if(root== nullptr){
            newRoot->left = newRoot->right = newRoot;
            this->root = newRoot;
            this->min = newRoot;
        } else {
            fnode* last = root->left;
            last->right->left = newRoot;
            newRoot->right = last->right;
            last->right = newRoot;
            newRoot->left = last;
        }
        rootNum++;
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
        if(y != root) {
            root = y ->right;
        }
        fnode* last = x->child;
        y->p = x;
        x->right= last->right;
        x->left = last->right->left;
        last->right->left = x;
        last->right = x;
        x->degree++;
        y->mark = false;
    }

    void cut(fnode* x, fnode* y);
    void cascading_cut(fnode* y);
};
