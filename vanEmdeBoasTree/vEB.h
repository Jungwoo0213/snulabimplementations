#ifndef VEB
#define VEB

#include <iostream>
#include <math.h>

using namespace std;

class vEB{
public:
    int u;
    

    vEB(int u){
        if(isPowerOfTwo(u)==false){
            cout << "u is not power of 2"<<endl;
        }
    }

private:
    int high(int x){
        
    }

    bool isPowerOfTwo(int x){
        return (x!=0) && ((x & (x-1))==0);
    }


};

#endif