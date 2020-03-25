#include <iostream>
#include <math.h>

using namespace std;

class HeapSort{
public:
	int* A;
	int size;
    int len;

	bool MaxHeap;

	inline int left(int ind){
		return (ind << 1)+1;
	}
	inline int right(int ind){
		return (ind << 1)+2;
	}
	
	HeapSort(int *tA, int size, bool ifMax = true){
        A = tA;
        this->size = len = size;
		MaxHeap = ifMax;
	}
	void MaxHeapify(int i){
		int l = left(i);
		int r =right(i);
		int largest = i;
		if(l< size && A[l]>A[i])
			largest = l;
		if(r< size && A[r] > A[largest])
			largest = r;
		if (largest != i){
            swap(i, largest);
            MaxHeapify(largest);
		}
	}
    void buildHeap(){
        size = len;
        for( int i=floor(len/2)-1; i>=0; i--)
            MaxHeapify(i);
    }
    void sort(){
        buildHeap();
        for(int i=len-1; i>=1; i--){
            swap(0, i);
            size--;
            MaxHeapify(0);
        }
    }
    void print(){
        for(int i=0; i<len;i++){
            cout << A[i]<<" ";
        }
        cout <<endl;
    }
    void check(){
        int a, b;
        for(int i=0;i<len-1;i++){
            a = A[i];
            b = A[i+1];
            if(a>b)
                cout << "Sort is wrong"<<endl;
        }
        cout << "Sort is correct!"<<endl;
    }
private:
    inline void swap(int i, int j){
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
};
