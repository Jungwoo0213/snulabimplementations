#ifndef VEB
#define VEB

#include <iostream>
#include <math.h>

using namespace std;

class vEB{
public:
    vEB* summary;
    vEB** cluster;

    vEB(int u){
        if(isPowerOfTwo(u)==false){
            cout << "u is not power of 2"<<endl;
        }
        this->u = u;
        cluster = new vEB*[highSqrt()];
    }
    int* minimum(){
        return min;
    }
    int* maximum(){
        return max;
    }
    bool isMember(int x){
        if( x==*min || x==*max)
            return true;
        else if(u==2)
            return false;
        else
            return cluster[high(x)]->isMember(low(x));
    }
    int* successor(int x){
        if(u==2){
            if(x==0 && *max==1)
                return &((int){1});
            else
                return nullptr;
        } else if(min != nullptr && x < *min){
            return min;
        } else {
            int *max_low = cluster[high(x)]->maximum();
            if(max_low != nullptr && low(x)<*max_low){
                int *offset = cluster[high(x)]->successor(low(x));
                return &((int){index(high(x), *offset)});
            } else {
                int* succ_cluster = summary->successor(high(x));
                if(succ_cluster == nullptr)
                    return nullptr;
                else {
                    int* offset = cluster[*succ_cluster]->minimum();
                    return &(int){index(*succ_cluster, *offset)};
                }
            }
        }
    }

private:
    int u;
    int *min;
    int *max;

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
        return  1 << int(floor(log2(double(u))/2));
    }
    int highSqrt(){
        return 1 << int(ceil(log2(double(u))/2));
    }
    bool isPowerOfTwo(int x){
        return (x!=0) && ((x & (x-1))==0);
    }
};

#endif