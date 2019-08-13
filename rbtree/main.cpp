#include "rbtree.h"

#include <iostream>
#include <assert.h>
using namespace std;

using namespace std;

int main(){
    RBTree* tr = new RBTree();


    tr->insert(41);
    tr->insert(38);
    tr->insert(31);
    tr->insert(12);
    tr->insert(19);
    tr->insert(8);

    assert(!tr->erase(9));
    tr->erase(8);
    tr->erase(12);
    tr->erase(19);
    tr->erase(31);
    tr->erase(38);
    tr->erase(41);

    tr->insert(41);
    tr->insert(38);
    tr->insert(31);
    tr->insert(12);
    tr->insert(19);
    tr->insert(8);

    RBNode* u = tr-> search(9);
    if(u != tr->nil){
        cout << "WRONG: Search is not nil" << endl;
        return 1;
    }
    u = tr->search(8);
    while(u!= tr->nil){
        cout << u->key<<endl;
        u = tr->successor(u);
    }
    cout << endl;

    cout << "root key: " << tr->root->key << endl;
    cout << "left key: " << tr->root->left->key << endl;
    cout << "right key: " << tr->root->right->key << endl;
    cout << "19 left key: " << tr->root->left->left->key << endl;

    u = tr->search(41);
    while(u != tr->nil){
        cout << u->key<<endl;
        u = tr->predecessor(u);
    }
    cout << endl;

    cout << "MAX = " << tr->maximum(tr->root)->key <<endl;
    cout << "MIN = " << tr->minimum(tr->root)->key <<endl;

    return 0;
}