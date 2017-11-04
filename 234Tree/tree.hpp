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
#include "fileStreamUtils.hpp"

class tree {
private:
    node* root = 0;
    queue<node*> q;
        
public:
    tree();
    ~tree();
    node* search(int ele);
    node* getInsertNode(int ele);
    node* getSuccessorNode(node* n, int ele);
    
    int insert(int ele);
    int deleteE(int ele);
    
    string show();
};
#endif /* tree_hpp */
