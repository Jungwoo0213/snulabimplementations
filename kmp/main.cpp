#include <iostream>

#include "kmp.h"

int main(){
    kmp KMP("pattern.txt", "text.txt");

    KMP.kmp_matcher();

    return 0;
}