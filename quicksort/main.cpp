#include <iostream>

#include "QuickSort.h"

using namespace std;



int main(){
    int A[] = {34, 25, 342,134,342};

    QuickSort QS(A, 0, 4);

    for(int i=0; i<5; i++){
        cout << A[i]<<" ";
    }
    return 0;
}