//
//  TreeController.cpp
//  234Tree
//
//  Created by Minseok Choi on 16/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include "fileStreamUtils.hpp"

int fileStreamUtils::saveStr(string str){
    if (fileOutputStream.is_open()) {
        fileOutputStream << str + "\n" << endl;
        return 0;
    } else return -1;
}

queue<string> fileStreamUtils::queueingInputs(){
    queue<string> q;
    char* tok = " ";
    char* input = strtok(oriFileContents, tok);
    while (input != NULL) {
        q.push(input);
        input = strtok(NULL, tok);
    }

    return q;
}

int fileStreamUtils::openOutputStream(string fileName){
    fileOutputStream.open(fileName, ios::out|ios::app);
    if(!fileOutputStream.is_open()) return -1;
    else return 0;
}

int fileStreamUtils::openInputStream(string fileName){
    fileInputStream.open(fileName, ios::in|ios::ate);
    streampos size;
    
    if(fileInputStream.is_open()){
        size = fileInputStream.tellg();
        oriFileContents = new char[size + (streampos)1];
        fileInputStream.seekg(0, ios::beg);
        fileInputStream.read(oriFileContents, size);
        oriFileContents[size] = 0;
        
        cout << oriFileContents << endl;
        
    } else {
        return -1;
    }
    
    return 0;
}

int fileStreamUtils::closeStreams(){
    fileInputStream.close();
    fileOutputStream.close();
    if(oriFileContents != NULL) delete [] oriFileContents;
    return 0;
}

fileStreamUtils::~fileStreamUtils(){
    closeStreams();
}
