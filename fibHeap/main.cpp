#include <iostream>
#include "fibHeap.h"
#include <assert.h>

using namespace std;

int main(){
    fibHeap* fHeap = new fibHeap();

    fnode* node13 = fHeap->insert(13);
    fHeap->insert(52);
    fHeap->insert(3);
    fHeap->insert(18);
    fHeap->insert(39);
    fHeap->insert(52);
    fHeap->insert(38);
    fHeap->insert(41);

    //cout << node13->key << endl;
    fnode* cur = fHeap->root;
    for(int i=0; i<fHeap->num;i++){
        cout<<cur->key<< " ";
        cur = cur->right;
    }
    cout << endl;

    fnode* exMin = fHeap->extract_min();

    cout << exMin->key << endl;

    return 0;
}