#include <stdio.h>
#include <stdlib.h>
#include "avl_utils.c"

int main(int argc, char const *argv[])
{
    int left[16] = {3,5,2,7,4,21,23,25,8,14,15,16,17,18,19,20};
    int right[5]= {56,34,45,78,91};

    node *T1 = NULL, *T2= NULL;
    
    for(size_t i = 0; i < 16; i++)
    {
        T1 = insert(T1,left[i]);
    }
    
    for(size_t i = 0; i < 5; i++)
    {
        T2 = insert(T2, right[i]);
    }
    
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
    
    printf("The resulting tree printed in inorder fashion :\n");
    display(T1);
    
    return 0;
}
