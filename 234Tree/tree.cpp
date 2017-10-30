//
//  tree.cpp
//  234Tree
//
//  Created by Minseok Choi on 29/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include "tree.hpp"

tree::tree(){
    root = new node();
}

node* tree::search(int ele){
    node* searchNode = root;
    
    while (searchNode != NULL) {
        int* eles = searchNode->getElementsAll();
        for (int i=1; i<eles[SIZE]+1; i++) {
            if (ele > eles[i]) continue;
            else if(ele == eles[i]) return searchNode;
            else {
                searchNode = searchNode -> getChildrenAll()[i-1];
                break;
            }
        }
    }
    
    return searchNode;
}

node* tree::getInsertNode(int ele){
    node* searchNode = root;
    node* parentSearchNode = NULL;
    
    while (searchNode != NULL) {
        int i = 1;
        int* eles = searchNode->getElementsAll();
        for (; i<eles[SIZE]+1; i++) {
            if (ele > eles[i]) continue;
            else break;
        }
        parentSearchNode = searchNode;
        searchNode = searchNode -> getChildrenAll()[i-1];
    }
    
    return parentSearchNode;
}

int tree::insert(int ele){
    node* insertNode = getInsertNode(ele);
    node* parent = insertNode->getParent();
    insertNode->addElement(ele);
    while(insertNode->getSize() == 4){
        int e = insertNode->split();
        if(parent == NULL) {
            parent = new node(e);
            root = parent;
        }
        else parent->addElement(e);
        
        node::addChild(parent);
        
        // 메모리 해제해야 하는 경우가 더 있는지 확인해봐야한다.
        // 1. 4노드를 초과하는 경우 -> split한 후에 original node를 delete
        delete [] insertNode;
        
        insertNode = parent;
        parent = insertNode->getParent();
    }
    return 0;
}

int tree::show(){
    int childFloorNum=0;
    int floorNum = 1;
    q.push(root);
    
    // while문은 level 수 만큼 loop를 돕니다.
    // floorNum 변수에는 해당 level의 node 숫자가 들어있습니다.
    while (!q.empty()) {
        childFloorNum = 0;
        for (int i=0; i<floorNum; i++) {
            node* p = q.front(); q.pop();
            cout << p->getStringAllElements();
            
            if(p->getChildrenAll()[1] == NULL) continue;
            
            int size = p->getSize()+1;
            for (int j=0; j<size; j++) {
                q.push(p->getChildrenAll()[j]);
            }
            childFloorNum += size;
        }
        cout << endl;
        floorNum = childFloorNum;
    }
    return 0;
}
