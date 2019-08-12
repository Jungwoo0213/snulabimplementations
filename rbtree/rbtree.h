class RBNode {
public:
    static const int RED = 0;
    static const int BLACK = 1;
    int key;
    int color;
    RBNode *left;
    RBNode *right;
    RBNode *p;
};

class RBTree{
public:
    RBNode *root;
    RBNode *nil;
    RBTree(){
        nil = new RBNode;
        nil->left = nil->right = nil->p = nil;
        nil-> key = 0;
        nil-> color = RBNode::BLACK;
        root = nil;
    }
    RBNode* search(int key);
    RBNode* minimum(RBNode* current);
    RBNode* maximum(RBNode* current);
    RBNode* successor(RBNode* current);
    RBNode* predecessor(RBNode* current);

    //rotations
    void left_rotate(RBNode* z);
    void right_rotate(RBNode* z);

    //insertions
    void insert_fixup(RBNode* z);
    bool insert(int key); // true if inserted, false if already exist -> not inserted

    //deletions
    void transplant(RBNode* u, RBNode* v);
    bool erase(RBNode* z);


};