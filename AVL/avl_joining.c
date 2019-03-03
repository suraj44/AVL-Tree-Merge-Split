#include <stdio.h>
#include <stdlib.h>
#include "avl_utils.c"

int main(int argc, char const *argv[])
{
    int left[5] = {22,10,25,20,15};
    int right[3]= {80,35,30};

    node *T1 = NULL, *T2= NULL;
    
    for(size_t i = 0; i < 5; i++)
    {
        T1 = insert(T1,left[i]);
    }
    
    for(size_t i = 0; i < 3; i++)
    {
        T2 = insert(T2, right[i]);
    }
    
    
    int h1 = T1->height;
    int h2 = T2->height;

    printf("h1: %d, h2: %d\n", h1, h2);
    display(T1);
    display(T2);
    printf("%d %d %d\n", T2->val, height(T2->left), height(T2->right));

    if(h1 > h2) {
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

        printf("HEIGHT: %d\n", height(u->left)-height(u->right));
        
        printf("The resulting tree printed in inorder fashion :\n");
        display(T1);
    } else {
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

        printf("HEIGHT: %d\n", height(u->left)-height(u->right));
        
        printf("The resulting tree printed in inorder fashion :\n");
        display(T2);

    }
    
    
    
    return 0;
}
