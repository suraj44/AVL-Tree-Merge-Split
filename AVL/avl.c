#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


node* new_node(int val){
    node* n = (node*)malloc(sizeof(node));
    n->val= NULL;
    n->right = NULL;
    n->left = NULL;
    n->height = 0;
    return n;
}


node* left_rotate(node* root) {
    int left = root->left->val;
    int tmp = root ->val;
    root->val = left;
    root->left->val = tmp;
}

node * insert(node *root, int val) {  
    if (root->val == NULL) 
        return new_node(val);
    int currVal = root->val;
    if(val < currVal) {
        insert(root->left, val);
    } else if ( val > currVal) {
        insert(root->right, val);
    } else {
        return root;
    }

}

int main() {

}