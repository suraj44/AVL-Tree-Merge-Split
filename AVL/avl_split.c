#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_utils.h"

int main(int argc, char const *argv[])

{
    int values[] = {40, 20, 60, 10, 30, 80, 15, 25, 35, 22,70};
    
    node *T1 = NULL;
    
    for(size_t i = 0; i < 10; i++)
    {
        T1 = insert(T1,values[i]);
    }

    // node * dummy = split_tree(T1, 60);

    node * dummy = split_2(T1, 60);

    printf("The values less than the given key are : ");
    display(dummy->left);
    printf("\nThe values greater than the given key are : ");
    display(dummy->right);


    return 0;
}