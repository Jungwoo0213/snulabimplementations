#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class kmp{
public:
    string P;
    int pLength;
    string T;
    int TLength;
    int* pi;

    kmp(string* pName, string* TName){
        ifstream ifsp, ifsT;

        ifsp.open(*pName, ios::in);
        P.assign((istreambuf_iterator<char>(ifsp)), (istreambuf_iterator<char>()));

        ifsT.open(*TName, ios::in);
        T.assign((istreambuf_iterator<char>(ifsT)), (istreambuf_iterator<char>()));

    }

    void kmp_matcher(){
        int n = T.length();
        int m = P.length();
        pi = compute_prefix_function();
        int q=0;
        for (int i=1; i<=n; i++){
            while(q>0 && P[q] != T[i-1]){
                q = pi[q-1];
            }
            if(P[q]==T[i-1])
                q = q+1;
            if(q==m){
                cout << "Pattern occurs with shift "<< i-m <<endl;
                q = pi[q-1];
            }
        }
    };

    int* compute_prefix_function(){
        int m = P.length();
        int* temp_pi = new int[m];
        temp_pi[0] = 0;
        int k = 0;
        for (int q=0; q<=m; q++){
            while(k>0 && P[k] != P[q-1])
                k = temp_pi[k-1];
            if (P[k] == P[q-1])
                k = k+1;
            temp_pi[q-1] = k; 
        }
        return temp_pi;
    }

private:

};