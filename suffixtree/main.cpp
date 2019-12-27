#include <iostream>

#include "suffixtree.h"

int main(){
    string TEXT = "banana";
    SuffixTree ST(TEXT);
    ST.search("ana");
    return 0;
}