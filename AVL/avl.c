#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#ifndef max
#define max(a,b)            (((a) >= (b)) ? (a) : (b))
#endif

void print_elapsed(clock_t start, clock_t stop)
{
  double elapsed = ((double) (stop - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time: %fs\n", elapsed);
}


node* new_node(int val){
    node* n = (node*)malloc(sizeof(node));
    n->val= val;
    n->right = NULL;
    n->left = NULL;
    n->height = 1;
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

int main(int argc, char*argv[]) {
    srand(time(NULL));
    clock_t start, stop;
    NUM_VALS = (long long int)atoll(argv[1]);

    int *values = (int*)malloc(NUM_VALS * sizeof(int));

    FILE *f = fopen("data.txt", "r");

    node * root = NULL;
    printf("Adding values to tree..\n");
    for(int i=0;i< NUM_VALS; i++) {
        fscanf(f, "%d\n", &values[i]);
        // printf("%d ",values[i]);
        root = insert(root,values[i]);
    }
    printf("\n");

    int index = rand() % NUM_VALS;

    start = clock();
    node * key = search_node(root, values[index]);
    stop = clock();
    print_elapsed(start, stop);





    // while(1) {
    //     int ch;
    //     printf("1. Search for a value, 2. Delete a value, 3. Display anything else to exit\n");
    //     scanf("%d", &ch);
    //     switch(ch) {
    //         case 1:
    //             printf("Enter a value to search for:\n");
    //             int search;
    //             scanf("%d", &search);
    //             start = clock();
    //             node * key = search_node(root, search);
    //             stop = clock();
    //             if(key == NULL){
    //                 printf("The value is not found\n");
    //             }
    //             else printf("The value is found\n");
    //             print_elapsed(start,stop);
    //             break;
    //         case 2:
    //         printf("Enter a value to delete:\n");
    //             int del;
    //             scanf("%d", &del);
    //             root = delete_node(root, del);
    //             break;

    //         case 3 :
    //         display(root);
    //         break;
    //         default:
    //             printf("exiting...\n");
    //             exit(0);

    //     }
    // }

}

