#include <iostream>
#include <fstream>

#include "suffixtree.h"

using namespace std;

int main(){
    ifstream fs;
    fs.open("TEXT.txt");    
    //string TEXT = "banana";
    string TEXT((istreambuf_iterator<char>(fs)),
                (istreambuf_iterator<char>()) );
    SuffixTree ST(TEXT);
    ST.search("by");
    return 0;
}