
class fnode{
    int key;
    int right;
    int left;
    int p;
};

class fibHeap {
public:
    int num;
    fnode *root;
    
    fibHeap(){  
        num = 0;
        root = nullptr;
    }
    void make_heap();
    bool insert(int key);
    fnode* minimum();
    fnode* extract_min();
    fibHeap* join(const fibHeap* H1, const fibHeap* H2);

    bool decrease_key(int oldKey, int newKey);
    bool erase(int key);
};
