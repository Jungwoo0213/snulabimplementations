#include <iostream>
#include <stdlib.h>
#include "heapsort.h"

using namespace std;

const int size =100;
int A[size];


int main(){

    srand(1);
    for(int i=0; i<size; i++)
        A[i] = rand()%100;

    HeapSort hp(A, size);
    hp.sort();
    hp.print();
    hp.check();

	return 0;
}
