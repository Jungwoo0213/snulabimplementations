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
        return floor((double)x/lowerSqrt());
    }
    int low(int x){
        return x % lowerSqrt();
    }
    int index(int x, int y){
        return x*lowerSqrt() + y;
    }
    int lowerSqrt(){
        return  1 << int(floor(log2((double)u)/2));
    }
    bool isPowerOfTwo(int x){
        return (x!=0) && ((x & (x-1))==0);
    }


};

#endif