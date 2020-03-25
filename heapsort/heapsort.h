#include <iostream>
using namespace std;

class HeapSort{
	int* A;
	int size;

	bool MaxHeap;

	inline int left(int ind){
		return (ind << 1)+1;
	}
	inline int right(int ind){
		return (ind << 1)+2;
	}
	
	HeapSort(bool ifMax = true){
		MaxHeap = ifMax;
	}
	void MaxHeapify(int i){
		int l = left(i);
		int r =right(i);
		int largest = i;
		if(l<= size && A[l]>A[i])
			largest = l;
		if(r<= size && A[r] > A[largest])
			largest = r;
		if (largest != i){
            int temp = A[i];
            A[i] = A[largest];
            A[largest] = temp;
            MaxHeapify(largest);
		}
	}
};
