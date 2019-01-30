#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#ifndef max
#define max(a,b)            (((a) >= (b)) ? (a) : (b))
#endif


node* join(node* T1, node* T2){
    if(height(T1) > height(T2)) {
        joinLeft(T1, T2);
    } else {
        joinRight(T1,T2);
    }
}

node* joinLeft(node* T1, node* T2) {
    int h1 = T1->height;
    int h2 = T2->height;
    node * temp = T2;
    while(temp->left) temp=temp->left;
    int x = temp->val;

    T2 = delete_node(T2, x);
    int h = T2->height;
    
    node *v = T1, *u=T1;
    int h_prime = h1;
    while (h_prime >= h+1){
        if(balance_factor(v)==-1) h_prime -= 2;
        else h_prime -=1;
        u = v;
        v = v->right;
    }
    
    node* new_tree = new_node(x);
    new_tree->left = v;
    new_tree->right= T2;
    new_tree->height = 1 + max(height(new_tree->left),height(new_tree->right));

    
    u->right = new_tree;

    T1 = insert(T1, v->val);
    return T1;
}

node* joinRight(node* T1, node* T2) {
    int h1 = T1->height;
    int h2 = T2->height;

    node * temp = T1;
        while(temp->right) temp=temp->right;
        int x = temp->val;

        T1 = delete_node(T1, x);
        int h = T1->height;

        node *v = T2, *u=T2;
        int h_prime = h2;
        while (h_prime >= h+1){
            if(balance_factor(v)==1) h_prime -= 2;
            else h_prime -=1;
            u = v;
            v = v->left;
        }
 
        node* new_tree = new_node(x);
        new_tree->right = v;
        new_tree->left= T1;
        new_tree->height = 1 + max(height(new_tree->left),height(new_tree->right));

        
        
        u->left = new_tree;

        T2 = insert(T2, v->val);
        return T2;
}


node* split(node* t, int k) {
    if (t==NULL) {
        return new_node(-1);
    }

    if(t->val == k) {
        node* temp = new_node(0);
        temp->left=t->left;
        temp->right=t->right;

        temp->height = max(height(temp->left), height(temp->right)) +1;
        return temp;    
    }
    if(k < t->val) {
        node* temp = split(t->left, k);
        temp->right = join(temp->right, t->right);
        temp->right = insert(temp->right, t->val);
        return temp;
    }
    if(k > t->val) {
        node* temp = split(t->right,k);
        temp->left = join(t->left, temp->left);
        temp->left = insert(temp->left, t->val);
        return temp;
    }
}


node* new_node(int val){
    node* n = (node*)malloc(sizeof(node));
    n->val= val;
    n->right = NULL;
    n->left = NULL;
    n->height = 0;
    return n;
}

int height(node* root) {
    if(root== NULL)
        return 0;
    return root->height;
}

node* left_rotate(node* root) {
    node * right = root->right;
    node * right_child = right->left;

    root->right = right_child;
    right->left = root;

    root->height = max(height(root->right), height(root->left)) + 1;
    right->height = max(height(right->right), height(right->left)) + 1;

    return right;
}

node* right_rotate(node* root) {
    node* left = root->left;
    node* left_child = left->right;

    left->right = root;
    root->left = left_child;

    root->height = max(height(root->right), height(root->left)) + 1;
    left->height = max(height(left->right), height(left->left)) + 1;

    return left;


}


int balance_factor(node* root) {
    int balance_factor = height(root->left) - height(root->right);
    return balance_factor;
}

node * insert(node *root, int val) {  
    if (root == NULL) 
        return new_node(val);
    int currVal = root->val;
    if(val < currVal) {
        root->left = insert(root->left, val);
    } else if ( val > currVal) {
        root->right = insert(root->right, val);
    } else {
        return root;
    }

    root->height = max(height(root->right), height(root->left)) + 1;

    int bf = balance_factor(root);
    if(bf > 1 && val < root->left->val) {
        return right_rotate(root);
    }
    if (bf < -1 && val > root->right->val ) {
        return left_rotate(root);
    }
    if(bf > 1 && val > root->left->val) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (bf < -1 && val < root->right->val) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

node * inorder_successor(node* root){
    node* temp = root->right;

    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

node* delete_node(node * root, int val){
    if (root==NULL){
        return root;
    }
    if(val < root->val){
        root->left = delete_node(root->left, val);
    }
    else if (val > root->val){
        root->right = delete_node(root->right, val);
    }
    // if found
    else {
        // printf("%p %p %d\n",root->left, root->right, root->val);
        // zero or one child
        if((root->left==NULL || root->right == NULL)){
            node * temp = root->left ? root->left: root->right;

            // no children case - delete root
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else{ // One child case
                *root = *temp;
            }
            // printf("Value found\n");
            free(temp);
        }
        // two children
        else {
            node * temp = inorder_successor(root);
            // printf("succ : %d\n",temp->val);
            root->val = temp->val;
            root->right  = delete_node(root->right, temp->val);
        }
    }

    if (root == NULL){
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balance_factor(root);

    // Left left case
    if(bf>1 && balance_factor(root->left)>=0){
        return right_rotate(root);
    }

    // Right right case
    if(bf<-1 && balance_factor(root->right)<=0){
        return left_rotate(root);
    }

    // Left Right case
    if(bf>1 && balance_factor(root->left)<0){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Left case
    if(bf<-1 && balance_factor(root->right)>0){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

node * search_node(node * root, int val){
    if(root == NULL || root->val == val){
        return root;
    }

    else if (val < root->val){ 
        return search_node(root->left, val);
    }
    else if (val > root->val){
        return search_node(root->right, val);
    }
}

void display_tree(node* root){
    if(root == NULL){
        return;
    }
    display_tree(root->left);
    printf("%d ",root->val);
    display_tree(root->right);
}

void display(node * root){
    display_tree(root);
    printf("\n");
}