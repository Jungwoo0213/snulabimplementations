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
    bool insRoot(fnode* newRoot){\
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
    fnode* minimum();
    fnode* extract_min();
    void consolidate(fibHeap* H);
    fibHeap* join(const fibHeap* H2);

    bool decrease_key(fnode* oldNode, int newKey);
    bool erase(int key);
};
