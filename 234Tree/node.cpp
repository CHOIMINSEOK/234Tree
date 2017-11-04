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
    if (elements[SIZE]==0) {
        return "elements가 존재하지 않습니다.";
    }
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

/*
 *  - 상위클래스 tree에 의하여
 *    input parameter idx의 유효성을 보장받는다.
 */
node* node::getChild(int idx){
    return children[idx];
}
/*
 *  - 외부에서 child node가 추가되는 경우에는 delete의 fusion 경우뿐이다.
 *  (insert의 split된 node는 addChildFromQueue에서 처리)
 *  => fusion case에도 child는 맨 앞 index 또는 맨 뒤 index에 추가되는 경우만 존재한다.
 *  - element의 유효성에 관여하지 않는다.
 *  - 추가된 child와 관계하는 element는 tree에 의해 추가됨을 보장받는다.
 */
node* node::addChild(int idx, node* child){
    int i = elements[SIZE];
    for (; i>=idx; i--) {
        children[i+1] = children[i];
        children[i] = NULL;
        
    }
    
    children[idx] = child;
    if(child!=NULL) children[idx]->parent = this;
    return 0;
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
        if(parent->getChild(myidx)==this) break;
        myidx++;
    }
    return myidx;
}

int node::getSize(){
    return elements[SIZE];
}

/*
 *  - 자신을 포함한 sibling node의 갯수를 반환합니다.
 */
int node::getSiblingNum(){
    return parent->getSize()+1;
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
node* node::getSibling(){
    int myidx = getIdxOnParent();
    
    if(myidx==0) return parent->getChild(myidx+1);
    
    if (myidx==parent->getSize()) return parent->getChild(myidx-1);
    
    int siblingOffset = parent->getChild(myidx+1)->getSize() > parent->getChild(myidx-1)->getSize() ? 1 : -1;
    return parent->getChild(myidx+siblingOffset);
}

/*
 * return
 * : -1 -> 노드 입력범위 초과
 *  - children의 유효성에 대해 관여하지 않는다.
 *  - 추가된 element에 의해 빈 children은 tree 의해 채워짐을 보장받는다.
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

int node::addElementByIdx(int ele, int idx){
    int i = elements[SIZE];
    for (; i>idx; i--) {
        if (elements[i] >= ele) {
            elements[i+1] = elements[i];
        
            children[i+1] = children[i];
            children[i] = NULL;
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
 *  - 상위 클래스 tree에 의해서
 *    항상 삭제할 element가 존재하는 node에서만 호출됨을 보장받는다.
 */
//XXX : 같은 element를 삭제할때, 맨뒤 element를 삭제하려고했지만 앞의 element가 삭제될 잠재적 버그가 있다.
int node::eliminateElement(int ele){
    int size = elements[SIZE];
    
    if(size==0) return -1;
    int i=1;
    for (; i<size; i++) {
        if (elements[i]<ele) continue;
        
        elements[i] = elements[i+1];
    
        children[i] = children[i+1];
        children[i+1] = NULL;
        
    }
    elements[SIZE]--;
    
    return 0;
}

/*
 *  - 같은 element가 존재할 때 생기는 이슈로 인해 idx로 element를 삭제하는 function 추가
 */
int node::eliminateElementByIdx(int idx, int direc){
    int size = elements[SIZE];
    int dltedEle = elements[idx];
    
    for (int i=idx; i<size+1; i++) {
        elements[i] = elements[i+1];
        if (direc==FOR_FUSION) {
            children[i] = children[i+1];
            children[i+1] = NULL;
        } else {
            if (i==size && direc==FOR_TRANSFER_RIGHT) break;
            children[i-1] = children[i];
            children[i] = NULL;
        }

    }
    elements[SIZE]--;
    
    return dltedEle;
}

/*
 *  - 상위클래스 tree에 의해서
 *    대체될 element가 항상 존재하는 leaf node에서만 호출됨을 보장받는다.
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
 *  - 같은 element가 존재할 때 생기는 이슈로 인해 idx로 element를 변경하는 function 추가
 */
int node::changeElementByIdx(int oriIdx, int src){
    int oriEle = elements[oriIdx];
    elements[oriIdx] = src;
    
    return oriEle;
}

/*
 * - 상위클래스 tree에 의해서
 *   elements의 사이즈가 5인 node에서만 호출됨을 보장받는다.
 * - split된 node는 node class의 static queue에 저장되어서 addChildFromQueue 함수에서 쓰인다.
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
/*
 *  - split된 node들을 queue에서 꺼내 input node의 children으로 연결한다.
 */
int node::addChildFromQueue(node* n){
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

