//
//  main.cpp
//  234Tree
//
//  Created by Minseok Choi on 16/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include <iostream>
#include "fileStreamUtils.hpp"

int main(int argc, const char * argv[]) {

    fileStreamUtils treeController;
    if(treeController.openInputStream("input.txt") == -1) {
        cout << "파일이 존재하지 않습니다. " << endl;
    }
    
    if(treeController.openOutputStream("output.txt") == -1){
        cout << "output.txt를 생성하는데 문제가 발생했습니다." << endl;
    }
    
    queue<string> q = treeController.queueingInputs();
    while (!q.empty()) {
        treeController.saveStr(q.front());
        q.pop();
    }
    
    return 0;
}
