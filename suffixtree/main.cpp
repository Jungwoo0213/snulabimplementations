#include <iostream>
#include <fstream>

#include "suffixtree.h"

using namespace std;

int main(){
    //ifstream fs;
    //fs.open("TEXT.txt");    
    //string TEXT = "mississippi";
    //string TEXT = "abaaba";
    //string TEXT = "banana";
    string TEXT = "bbbbbababbbaabbbbb";
    //string TEXT((istreambuf_iterator<char>(fs)), (istreambuf_iterator<char>()) );
    SuffixTree ST(TEXT);
    ST.print();
    ST.search("a");
    return 0;
}