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

tree::~tree(){
    int childFloorNum=0;
    int floorNum = 1;
    q.push(root);
    
    // while문은 level 수 만큼 loop를 돕니다.
    // floorNum 변수에는 해당 level의 node 숫자가 들어있습니다.
    while (!q.empty()) {
        childFloorNum = 0;
        for (int i=0; i<floorNum; i++) {
            node* p = q.front(); q.pop();
            
            if(p->getChild(0) == NULL){
                delete [] p;
                continue;
            }
            
            int size = p->getSize()+1;
            for (int j=0; j<size; j++) {
                q.push(p->getChild(j));
            }
            
            childFloorNum += size;
            delete [] p;
        }
        cout << endl;
        floorNum = childFloorNum;
    }
}
/*
 * return :
 *  1. not NULL -> a pointer to the node including search element
 *  2. NULL -> no exist in tree
 */
node* tree::search(int ele){
    node* searchNode = root;
    
    while (searchNode != NULL) {
        int* eles = searchNode->getElementsAll();
        int i=1;
        for (; i<eles[SIZE]+1; i++) {
            if (ele > eles[i]) continue;
            else if(ele == eles[i]) {
                return searchNode;
            }
            else break;
        }
        searchNode = searchNode -> getChild(i-1);
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
        searchNode = searchNode -> getChild(i-1);
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
        
        node::addChildFromQueue(parent);
        
        // 메모리 해제해야 하는 경우가 더 있는지 확인해봐야한다.
        // - 4노드를 초과하는 경우 -> split한 후에 original node를 delete
        delete [] insertNode;
        
        insertNode = parent;
        parent = insertNode->getParent();
    }
    return 0;
}

/*
 *  - 해당 node의 element의 바로 전 successor node를 반환한다.
 */
node* tree::getSuccessorNode(node* n, int ele){
    node* parent = n;
    int size = n->getSize();
    for (int i=1; i<size+1; i++) {
        if (n->getElementsAll()[i]==ele) {
            n = n->getChild(i-1);
            break;
        }
    }
    while (n!=NULL) {
        parent = n;
        n = n->getChild(n->getSize());
    }
    return parent;
}

/*
 *  return :
 *    -1 -> no exist
 */
//TODO : 중복되는 코드 정리
int tree::deleteE(int ele){
    node* n = search(ele);
    if (n==NULL) return -1;
    
    node* successor = getSuccessorNode(n, ele);
    int successorNodeSize = successor->getSize();
    // internal node에 삭제할 element가 존재하는 경우
    // => successor leaf와 element change
    if (n!=successor) {
        int successEle = successor->changeElementByIdx(successorNodeSize, ele);
        n->changeElement(ele, successEle);
        successor->eliminateElementByIdx(successorNodeSize, FOR_TRANSFER_RIGHT); // 아무거나 상관없음. => 어차피 무조건 leaf node에서만 발생함
    } else {
        successor->eliminateElement(ele);
    }
    
    if (successorNodeSize==2 || successorNodeSize==3 || successor == root) return 0;
    
    // leaf node가 2node일 경우
    q.push(successor);
    
    while (!q.empty()) {
        n = q.front(); q.pop();
        if(n->getSize()!=0) break;
        
        node* sibling = n->getSibling();
        int nodeIdxOnParent = n->getIdxOnParent();
        int siblingIdxOnParent = sibling->getIdxOnParent();
        // transferOffset>0 이면 sibling은 right sibling이다.
        int transferOffset = (siblingIdxOnParent - nodeIdxOnParent + 1)/2;
        int parentEleIdx = nodeIdxOnParent + transferOffset;
        
        if (sibling->getSize()!=1) {
            //transfer
            int transferEleFromSibling = sibling->getElementsAll()[transferOffset>0 ? 1 : sibling->getSize()];
            node* transferChildFromSibling = sibling->getChild(transferOffset>0 ? 0 : sibling->getSize());
            
            int transferEleFromParent = n->getParent()->changeElementByIdx(parentEleIdx, transferEleFromSibling);
            n->addElement(transferEleFromParent);
            if (transferOffset>0) {
                n->addChild(1, transferChildFromSibling);
            } else {
                n->addChild(0, transferChildFromSibling);
            }
            
            sibling->eliminateElementByIdx(transferOffset>0 ? 1 : sibling->getSize(), transferOffset);
        } else {
            // fusion
            node* leftNode  = transferOffset>0 ? n : sibling;
            node* rightNode = transferOffset>0 ? sibling : n;
            
            int transferEleFromParent = leftNode->getParent()->eliminateElementByIdx(parentEleIdx, FOR_FUSION);
            leftNode->addElementByIdx(transferEleFromParent, leftNode->getSize());
            leftNode->addChild(leftNode->getSize(), rightNode->getChild(0));
            
            if(rightNode->getSize()==1){
                leftNode->addElement(rightNode->getElementsAll()[1]);
                leftNode->addChild(leftNode->getSize(), rightNode->getChild(1));
            }
            
            delete [] rightNode;
            if(leftNode->getParent()==root && root->getSize()==0){
                delete [] root;
                root = leftNode;
                break;
            }
            q.push(leftNode->getParent());
        }
    }

    return 0;
}

string tree::show(){
    int childFloorNum=0;
    int floorNum = 1;
    string ret = "";
    q.push(root);
    q.push(NULL);
    
    // while문은 level 수 만큼 loop를 돕니다.
    // floorNum 변수에는 해당 level의 node 숫자가 들어있습니다.
    while (!q.empty()) {
        childFloorNum = 0;
        for (int i=0; i<floorNum; i++) {
            node* p = q.front(); q.pop();
            if (p==NULL) {
                ret += "/";
                p = q.front(); q.pop();
            }
            
            ret += p->getStringAllElements();
            
            if(p->getChild(0) == NULL) continue;
            
            int size = p->getSize()+1;
            for (int j=0; j<size; j++) {
                q.push(p->getChild(j));
            }
            q.push(NULL);
            childFloorNum += size;
        }
        q.pop();
        ret += "\n";
        floorNum = childFloorNum;
    }
    return ret;
}
