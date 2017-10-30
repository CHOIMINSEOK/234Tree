//
//  tree.hpp
//  234Tree
//
//  Created by Minseok Choi on 29/10/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <iostream>
#include <queue>
#include "node.hpp"

class tree {
private:
    node* root = 0;
    queue<node*> q;
        
public:
    tree();
    ~tree(); // 메모리 해제하는거 추가해야함.
    node* search(int ele);
    node* getInsertNode(int ele);
    int insert(int ele);
    int show();
};
#endif /* tree_hpp */
