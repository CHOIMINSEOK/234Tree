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

void parseUserInput(string input){
    char instr = input[INSTR];
    input.erase(INSTR, 1);
    
    switch(instr){
        case INSERT:
            cout << "INSERT : " << input << endl; break;
        case DELETE:
            cout << "DELETE : " << input << endl; break;
        case SEARCH:
            cout << "SEARCH : " << input << endl; break;
        default:
            cout << "잘못된 명령어입니다." << endl; break;
    }
    
}

int main(int argc, const char * argv[]) {
//    fileStreamUtils treeController;
//    if(treeController.openInputStream("input.txt") == -1) {
//        cout << "파일이 존재하지 않습니다. " << endl;
//    }
//
//    if(treeController.openOutputStream("output.txt") == -1){
//        cout << "output.txt를 생성하는데 문제가 발생했습니다." << endl;
//    }
//
//    queue<string> q = treeController.queueingInputs();
//    while (!q.empty()) {
//        parseUserInput(q.front());
//        treeController.saveStr(q.front());
//        q.pop();
//    }
    
    tree t;

    for (int i=1; i<20; i++) {
        int randomNumber = rand()%365;
        cout << "insert : " << randomNumber << endl;
        t.insert(randomNumber);
        t.show();
        cout << "======" << endl;
    }
    
    t.insert(16);
    t.show();

//    cout << "node split : " << n.split() << endl;
    
    return 0;
}
