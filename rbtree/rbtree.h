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

class RBTree {
public:
	RBNode *root;
	RBNode *nil;
	RBTree() {
		nil = new RBNode;
		nil->left = nil->right = nil->p = nil;
		nil->key = 0;
		nil->color = RBNode::BLACK;
		root = nil;
	}

	RBNode* search(int key);
	RBNode* minimum(RBNode* cur);
	RBNode* maximum(RBNode* cur);
	RBNode* successor(RBNode* cur);
	RBNode* predecessor(RBNode* cur);
	void left_rotate(RBNode* z);
	void right_rotate(RBNode* z);

	void insert_fixup(RBNode* z);
	bool insert(int key); // true if inserted, false if already exist -> not inserted

    void transplant(RBNode* u, RBNode* v);
    void erase_fixup(RBNode* x);
    bool erase(int key);

    /*
	void transplant(RBNode* u, RBNode* v){
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
        v->p = u->p;
    };
	void erase_fixup(RBNode* x){
         while( x != root and x->color == RBNode::BLACK){
            if (x==x->p->left){
                RBNode* w = x->p->right;
                if (w->color == RBNode::RED){
                    w->color = RBNode::BLACK;
                    x->p->color = RBNode::RED;
                    left_rotate(x->p);
                    w = x->p->right;
                }
                if( w->left->color == RBNode::BLACK && w->right->color==RBNode::BLACK){
                    w->color = RBNode::RED;
                    x = x->p;
                } else{
                    if(w->right->color == RBNode::BLACK){
                        w->left->color = RBNode::BLACK;
                        w->color = RBNode::RED;
                        right_rotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = RBNode::BLACK;
                    w->right->color = RBNode::BLACK;
                    left_rotate(x->p);
                    x = root;
                }
            } else
            {
                RBNode* w = x->p->left;
                if (w->color == RBNode::RED){
                    w->color = RBNode::BLACK;
                    x->p->color = RBNode::RED;
                    right_rotate(x->p);
                    w = x->p->left;
                }
                if( w->right->color == RBNode::BLACK && w->left->color==RBNode::BLACK){
                    w->color = RBNode::RED;
                    x = x->p;
                } else{
                    if(w->left->color == RBNode::BLACK){
                        w->right->color = RBNode::BLACK;
                        w->color = RBNode::RED;
                        left_rotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = RBNode::BLACK;
                    w->left->color = RBNode::BLACK;
                    right_rotate(x->p);
                    x = root;
                }
            }
            
        }
        x->color = RBNode::BLACK;
    };

	bool erase(int key){
        RBNode* z = search(key);
        if (z==nil) return false;

        RBNode* y = z;
        RBNode* x;
        int y_orig_color = y->color;
        if (z->left == nil){
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil){
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_orig_color = y->color;
            x = y->right;
            if (y->p == z)
                x->p = y;
            else{
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        if (y_orig_color == RBNode::BLACK)
            erase_fixup(x);
        
        delete z;
        return true;
    };
    */
};