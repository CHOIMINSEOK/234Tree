//
//  node.hpp
//  234Tree
//
//  Created by Minseok Choi on 21/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <iostream>
#include <queue>
#include <string>
#define SIZE 0
#define FOR_TRANSFER_RIGHT 0
#define FOR_TRANSFER_LEFT  1
#define FOR_FUSION         2


using namespace std;

class node{
private:
    int elements[5] = {0,};
    node* parent = NULL;
    node* children[5] = {0, };
    static queue<node*> q;
    
public:
    
    node();
    node(int ele);
    node(int* eles, node** cd);
    
    string getStringAllElements();
    
    node* getParent();
    void setParent(node* n);
    node* getChild(int idx);
    node* addChild(int idx, node* child);
    
    int* getElementsAll();
    node** getChildrenAll();
    int getFirstElement();
    int getIdxOnParent();
    int getSize();
    int getSiblingNum();
    
    node* getSibling();
    
    
    int addElement(int ele);
    int addElementByIdx(int ele, int idx);
    int split();
    
    int eliminateElement(int ele);
    int eliminateElementByIdx(int idx, int direc);
    int changeElement(int ori, int src);
    int changeElementByIdx(int oriIdx, int src);
    
    static int addChildFromQueue(node* n);
    
};


#endif /* node_hpp */
