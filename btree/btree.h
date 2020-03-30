class node{
public:
    int n; //number of keys
    bool isLeaf;
    int* keys;
    node** children;
    node(bool isLeaf, const int t){
        this->isLeaf = isLeaf;
        keys = new int[2*t-1];
        children = new node*[2 * t];
    }

};

class btree{
public:
    btree(int t): t(t) {
        root = new node(false, t);
        root->n = 0;
    }
    void search(int key){

    }
    void insert(int key){

    }

private:
    node* root;
    const int t; //minimum degree

    void split_child(node* x, int i){
        node* y = x->children[i];
        node* z = new node(y->isLeaf, t);
        z->n = t-1;
        for(int j=0; j< t-1 ;j++){
            z->keys[j] = y->keys[j+t];
        }
        if (!y->isLeaf){
            for(int j=0; j<t;j++)
                z->children[j] = y->children[j+t];
        }
        y->n = t-1;
        for(int j= x->n; j >=i; j--)
            x->children[j+1] = x->children[j];
        x->children[i+1] = z;
        for(int j=x->n-1; j >=i-1; j--)
            x->keys[j+1] = x->keys[j];
        x->keys[i] = y.keys[t-1];
        x->n++;
    }
    void diskRead(node* x){
        
    }
};