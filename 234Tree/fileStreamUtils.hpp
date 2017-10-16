//
//  ㅆㅆ.hpp
//  234Tree
//
//  Created by Minseok Choi on 16/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef TreeController_hpp
#define TreeController_hpp

#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>
#include <stdlib.h>

using namespace std;

class fileStreamUtils {
private:
    ifstream fileInputStream;
    ofstream fileOutputStream;
    char* oriFileContents = NULL;
    
public:
    ~fileStreamUtils();
    int openInputStream(string fileName);
    int openOutputStream(string fileName);
    int closeStreams();
    queue<string> queueingInputs();
    int saveStr(string str);
    
};
#endif /* TreeController_hpp */
