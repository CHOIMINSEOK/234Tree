//
//  node.cpp
//  234Tree
//
//  Created by Minseok Choi on 21/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#include "node.hpp"

// c++ 에서 static stl 사용하기
// 이해가 잘 안된다. => 찾아보기
queue<node*> node::q;

node::node(){}

node::node(int ele){
    elements[1] = ele;
    elements[SIZE]++;
}

node::node(int* eles, node** cd){
    elements[SIZE] = eles[SIZE];
    if(cd[0]!=NULL){
        children[0] = cd[0];
        children[0]->parent = this;
    }
    for (int i=1; i<=elements[SIZE]; i++) {
        elements[i] = eles[i];
        if(cd[i]){
            children[i] = cd[i];
            children[i]->parent = this;
        }
    }
}

string node::getStringAllElements(){
    string e = "(";
    int i=1;
    for (; i<elements[SIZE]; i++) {
        e += to_string(elements[i]) + " ";
    }
    e += to_string(elements[i]) + ")";
    return e;
}

node* node::getParent(){
    return parent;
}

void node::setParent(node* n){
    parent = n;
}

int* node::getElementsAll(){
    return elements;
}

node** node::getChildrenAll(){
    return children;
}

int node::getIdxOnParent(){
    int myidx = 0;
    
    while (1) {
        if(parent->getChildrenAll()[myidx]==this) break;
        myidx++;
    }
    return myidx;
}

int node::getSize(){
    return elements[SIZE];
}

int node::getFirstElement(){
    return elements[1];
}

/*
 *  - 상위클래스 tree에 의하여
 *    sibling이 반드시 존재하는 node에서만 호출됨을 보장받는다.
 *  => sibling이 없는 경우인 root만 존재하는 경우 tree클래스가 예외처리
 *
 *  - sibling 중 3,4 node가 우선 순위를 갖고 반환된다.
 */
//TODO : 좀더 깔끔하게 정리할것, parent->getChildrenAll 보기 않좋음
node* node::getSibling(){
    int myidx = getIdxOnParent();
    
    if(myidx==0) return parent->getChildrenAll()[myidx+1];
    
    if (myidx==parent->getSize()) return parent->getChildrenAll()[myidx-1];
    
    int siblingOffset = parent->getChildrenAll()[myidx+1]->getSize() > parent->getChildrenAll()[myidx-1]->getSize() ? 1 : -1;
    return parent->getChildrenAll()[myidx+siblingOffset];
}

/*
 * return
 * : -1 -> 노드 입력범위 초과
 */
int node::addElement(int ele){
    if(elements[SIZE]==4) return -1;
    
    int i = elements[SIZE];
    for (; i>SIZE; i--) {
        if (elements[i] >= ele) {
            elements[i+1] = elements[i];
            if(children[i] != NULL) {
                children[i+1] = children[i];
                children[i] = NULL;
            }
            continue;
        }
        else break;
    }
    
    elements[i+1] = ele;
    elements[SIZE]++;
    return 0;
}

/*
 *  return :
 *      -1 -> element가 존재하지않음
 *
 *  - 예외처리는 해놓았으나, 이 함수는 상위 클래스 tree에 의해서
 *    항상 삭제할 element가 존재하는 node에서만 호출됨을 보장받는다.
 */
int node::eliminateElement(int ele){
    int size = elements[SIZE];
    
    if(size==0) return -1;

    for (int i=1; i<size; i++) {
        if (elements[i]<ele) continue;
        
        elements[i] = elements[i+1];
        if(children[i] != NULL) {
            children[i] = children[i+1];
            children[i+1] = NULL;
        }
    }
    
    elements[SIZE]--;
    
    return 0;
}

/*
 *  - 상위클래스 tree에 의해서
 *    항상 대체될 element가 존재하는 node에서만 호출됨을 보장받는다.
 */
int node::changeElement(int ori, int src){
    int size = elements[SIZE];
    for (int i=1; i<size+1; i++) {
        if (elements[i] == ori) {
            elements[i] = src;
            break;
        }
    }
    
    return 0;
}

/*
 * - 상위클래스 tree에 의해서
 *   elements의 사이즈가 5인 node에서만 호출됨을 보장받는다.
 * - split된 node는 node class의 static queue에 저장되어서 addChild 함수에서 쓰인다.
 */
int node::split(){
    int ele1[3], ele2[2];
    node* cd1[3], *cd2[2];
    
    // 첫번째 split
    ele1[SIZE] = 2;
    cd1[0] = children[0];
    for (int i=1; i<3; i++) {
        ele1[i] = elements[i];
        cd1[i] = children[i];
    }
    
    node* child1 = new node(ele1, cd1);
    q.push(child1);
    
    // 두번째 split
    ele2[SIZE] = 1;
    ele2[1] = elements[4];
    cd2[0] = children[3];
    cd2[1] = children[4];
    
    node* child2 = new node(ele2, cd2);
    q.push(child2);
    
    return elements[3];
}

int node::addChild(node* n){
    if (q.empty()) return -1;

    int idxFirstNull = 0;

    while(1){
        if (n->children[idxFirstNull] == NULL) break;
        else idxFirstNull++;
    }
    if(idxFirstNull==0){
        n->children[idxFirstNull]   = q.front(); q.pop();
        n->children[idxFirstNull]->setParent(n);
        n->children[idxFirstNull+1] = q.front(); q.pop();
        n->children[idxFirstNull+1]->setParent(n);

    } else {
        n->children[idxFirstNull-1]   = q.front(); q.pop();
        n->children[idxFirstNull-1]->setParent(n);
        n->children[idxFirstNull] = q.front(); q.pop();
        n->children[idxFirstNull]->setParent(n);

    }

    
    return 0;
}

