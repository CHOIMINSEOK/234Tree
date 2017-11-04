//
//  main.cpp
//  234Tree
//
//  Created by Minseok Choi on 16/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include <iostream>
#include "fileStreamUtils.hpp"
#include "node.hpp"
#include "tree.hpp"

#include <cstdlib>

#define INSTR 0
#define INSERT 'i'
#define DELETE 'd'
#define SEARCH 's'


string parseUserInput(tree* t, string input){
    char instr = input[INSTR];
    input.erase(INSTR, 1);
    
    switch(instr){
        case INSERT:
            t->insert(stoi(input));
            return t->show();
             break;
        case DELETE:
            t->deleteE(stoi(input));
            return t->show();
            break;
        case SEARCH:
            return t->search(stoi(input))==NULL ? "no exist\n" : "exist\n";
            break;
        default:
            cout << "잘못된 명령어입니다." << endl; break;
    }
    return "-1";
    
}

int main(int argc, const char * argv[]) {
    tree* t = new tree();
    
    // batch mode
    if (argc!=1) {
        fileStreamUtils* fileStream = new fileStreamUtils();
        
        if(fileStream->openInputStream(argv[1]) == -1) {
            cout << "파일이 존재하지 않습니다. " << endl;
        }
        
        if(fileStream->openOutputStream("output.txt") == -1){
            cout << "output.txt를 생성하는데 문제가 발생했습니다." << endl;
        }
        
        queue<string> q = fileStream->queueingInputs();
        while (!q.empty()) {
            fileStream->saveStr(q.front());
            string ret = parseUserInput(t, q.front());
            fileStream->saveStr(ret);
            q.pop();
        }
        
        return 0;
    }
    
    // interactive mode
    string instr;
    while (1) {
        cout << "명령을 입력하세요(i,d,x) : " << endl;
        cin >> instr;
        cout << parseUserInput(t, instr) << endl;
    }
    
    return 0;

//    string instr;
//    while(1){
//        cout << "명령을 입력하세요(i,d,s) : " << endl;
//        system("clear");
//        cin >> instr;
//        parseUserInput(instr);
//    }
//
    //test case 1
//    string test[39] = {"i12", "i15", "i123", "i22", "i23", "i1", "i100", "i75", "i26", "i77", "i1"
//        , "i2", "i124", "i126", "i127", "i78", "i76", "i99", "i78", "i78", "i78", "i78", "i78", "i78"
//        , "d78", "d1", "d2", "d75", "d123", "d126", "d127", "d100", "d78", "d78", "d124", "d77", "d76"
//        , "d78", "d78"};
//
//    for (int i=0; i<39; i++) {
//        cout << "instruction : " << test[i] << endl;
//        parseUserInput(test[i]);
//
//    }
	//test case 2
//    int test[19] = { 53, 27, 75, 25, 70, 41, 38, 16, 59, 36, 73, 65, 60, 46, 55, 33, 68, 79, 48};
//    tree t;
//
//    for(int i=0;i<19;i++){
//        cout << "insert : " << test[i] << endl;
//        t.insert(test[i]);
//        t.show();
//    }
//    cout << "delete : " << 16 << endl;
//    t.deleteE(16);
//    t.show();
//    cout << "delete : " << 33 << endl;
//    t.deleteE(33);
//    t.show();
//    cout << "delete : " << 41 << endl;
//    t.deleteE(41);
//    cout << "delete : " << 46 << endl;
//    t.deleteE(46);
//    t.show();
//    cout << "delete : " << 36 << endl;
//    t.deleteE(36);
//    t.show();
//    cout << "delete : " << 27 << endl;
//    t.deleteE(27);
//    t.show();
//    cout << "delete : " << 25 << endl;
//    t.deleteE(25);
//    t.show();
//    cout << "delete : " << 53 << endl;
//    t.deleteE(53);
//    t.show();
//    cout << "delete : " << 65 << endl;
//    t.deleteE(65);
//    t.show();
//    cout << "delete : " << 59 << endl;
//    t.deleteE(59);
//    t.show();
//    cout << "delete : " << 55 << endl;
//    t.deleteE(55);
//    t.show();
//
//
//    return 0;
}
