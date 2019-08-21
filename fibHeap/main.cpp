#include <iostream>
#include "fibHeap.h"
#include <assert.h>

using namespace std;

int main(){
    fibHeap* fHeap = new fibHeap();

    fnode* node13 = fHeap->insert(13);
    fHeap->insert(52);
    fHeap->insert(18);
    fnode* node39  = fHeap->insert(39);
    fHeap->insert(54);
    fHeap->insert(38);
    fHeap->insert(41);
    fHeap->insert(3);

    //cout << node13->key << endl;
    fnode* cur = fHeap->root;
    for(int i=0; i<fHeap->num;i++){
        cout<<cur->key<< " ";
        cur = cur->right;
    }
    cout << endl;

    cout << "min key: " << fHeap->minimum()->key << endl;
    cout << "num: " << fHeap->num << endl;

    fnode* exMin = fHeap->extract_min();

    //decreasing key 

    fHeap->decrease_key(node39, 5);

    cout << fHeap->root->key << endl;
    cout << fHeap->root->right->key << endl;
    cout << fHeap->root->right->right->key << endl;
    cout << fHeap->root->right->right->right->key << endl;




    exMin = fHeap->extract_min();
    

    /*
    cout << "**main**" <<endl;
    cout << fHeap->root->key << endl;
    cout << fHeap->root->degree << endl;
    cout << fHeap->root->child->key << endl;
    cout << fHeap->root->child->left->key << endl;
    cout << fHeap->root->child->left->child->key << endl;
    cout << fHeap->root->left->key << endl;
    cout << fHeap->root->left->child->key << endl;
    */

    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();
    exMin = fHeap->extract_min();

    if (fHeap->minimum() != nullptr) cout << "cur min: "<<fHeap->minimum()->key << endl;
    if (exMin != nullptr) cout << "extracted: "<<exMin->key << endl;
    else cout << "exMin is NULL" <<endl;

    return 0;
}