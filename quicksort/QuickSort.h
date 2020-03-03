class QuickSort{
public:
    QuickSort(int* A, int p, int r){
        sort(A, p, r);
    }
private:
    int partition(int* A, int p, int r){
        int x = A[r];
        int i = p-1;
        for(int j=p; j<=r-1; j++){
            if(A[j]<=x){
                i++;
                swap(A, i, j);
            }
        }
        swap(A, ++i, r);
        return i;
    }
    void sort(int* A, int p, int r){
        if(p<r){
            int q = partition(A, p, r);
            sort(A, p, q-1);
            sort(A, q+1, r);
        }
    }
    void swap(int* A, int a, int b){
        int temp = A[a];
        A[a] = A[b];
        A[b] = temp;
    }
};