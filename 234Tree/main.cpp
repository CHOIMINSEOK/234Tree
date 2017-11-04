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

}
