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
    
    int* getElementsAll();
    node** getChildrenAll();
    int getFirstElement();
    int getIdxOnParent();
    int getSize();
    
    node* getSibling();
    
    
    int addElement(int ele);
    int split();
    
    int eliminateElement(int ele);
    int changeElement(int ori, int src);
    
    static int addChild(node* n);
    
};


#endif /* node_hpp */
