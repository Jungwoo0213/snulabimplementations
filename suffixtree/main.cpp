#include <iostream>
#include <fstream>

#include "suffixtree.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream fs;
    fs.open("TEXT.txt");    
    //string TEXT = "mississippi";
    //string TEXT = "abaaba";
    //string TEXT = "banana";
    //string TEXT = "bbbbbababbbaabbbbb";
    //string TEXT = "bbbbbababbbaabbbbbbbbbbababbbaabbbbb";
    string TEXT((istreambuf_iterator<char>(fs)), (istreambuf_iterator<char>()) );
    SuffixTree ST(TEXT);

    if(argc >= 2 && argv[1]=="s"){
        cout << "*****SUFFIX TREE*****"<<endl;
        ST.print();
        cout << endl;
    }

    if(argc >= 2 && argv[1]=="search"){
        string query;
        cout << "string to search: ";
        cin >> query;
        while(query != "exit"){
            ST.search(query);
            cout << "string to search: ";
            cin >> query;
        }
    }
    cout << argc <<endl;
    cout << argv[1]<<endl;

    return 0;
}