#include "rbtree.h"
#include <assert.h>

RBNode* RBTree::search(int key){
    RBNode* cur = root;
    while(cur != nil){
        if(cur->key == key)
            return cur;
        else if(cur->key > key)
            cur = cur->left;
        else
            cur = cur->right; 
    }
    return nil;
}
RBNode* RBTree::minimum(RBNode* current = nullptr){
    if(current == nullptr) current = root; 
    while(current->left != nil){
        current = current->left;
    }
    return current;
}
RBNode* RBTree::maximum(RBNode* current = nullptr){
    if(current == nullptr) current = root;
    while(current->right != nil){
        current = current->right;
    }
    return current;
}
RBNode* RBTree::successor(RBNode* cur){
    if(cur->right != nil){
        cur = cur->right;
        while(cur->left != nil)
            cur = cur->left;
        return cur;
    }
    while(cur->p != nil){
        if(cur->p->left == cur) return cur->p;
        cur= cur->p;
    }
    return nil;
}
RBNode* RBTree::predecessor(RBNode* cur){
    if(cur->left != nil){
        cur = cur->left;
        while(cur->right != nil)
            cur = cur->right;
        return cur;
    }
    while(cur->p != nil){
        if(cur->p->right == cur) return cur->p;
        cur = cur->p;
    }
    return nil;
}
void RBTree::left_rotate(RBNode* x){
    RBNode* y = x->right;
    assert(y != nil);

    x->right = y->left;
    if(y->left != nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == nil)
        root = y;
    else if( x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void RBTree::right_rotate(RBNode* x){
    RBNode* y = x->left;
    assert(y != nil);

    x->left = y->right;
    if(y->right != nil)
        y->right->p = x;
    y->p = x->p;
    if(x->p == nil)
        root = y;
    else if(x== x->p->right)
        x->p->right = y;
    else
        x->p->left = y;
    y->right = x;
    x->p = y;
}

void RBTree::insert_fixup(RBNode* z) {
	while (z->p->color == RBNode::RED) {
		if (z->p == z->p->p->left) {
			RBNode* y = z->p->p->right;
			if (y->color == RBNode::RED) {
				z->p->color = RBNode::BLACK;
				y->color = RBNode::BLACK;
				z->p->p->color = RBNode::RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					left_rotate(z);
				}
				z->p->color = RBNode::BLACK;
				z->p->p->color = RBNode::RED;
				right_rotate(z->p->p);
			}
		}
		else {
			RBNode* y = z->p->p->left;
			if (y->color == RBNode::RED) {
				z->p->color = RBNode::BLACK;
				y->color = RBNode::BLACK;
				z->p->p->color = RBNode::RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					right_rotate(z);
				}
				z->p->color = RBNode::BLACK;
				z->p->p->color = RBNode::RED;
				left_rotate(z->p->p);
			}
		}
	}
	root->color = RBNode::BLACK;
}

bool RBTree::insert(int key) {
	RBNode* y = nil;
	RBNode* x = root;
	while (x != nil) {
		y = x;
		if (key == x->key) return false;
		if (key < x->key) x = x->left;
		else x = x->right;
	}

	RBNode* z = new RBNode();
	z->key = key;
	z->left = nil;
	z->right = nil;
	z->color = RBNode::RED;
	z->p = y;
	if (y == nil) root = z;
	else if (z->key < y->key) y->left = z;
	else y->right = z;
	RBTree::insert_fixup(z);
	return true;
}

void RBTree::transplant(RBNode* u, RBNode* v){
    if (u->p == nil)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

void RBTree::erase_fixup(RBNode* x){
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
}

bool RBTree::erase(int key){
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
}