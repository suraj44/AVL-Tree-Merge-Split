#include <stdio.h>
#include <stdlib.h>
#include "avl_utils.c"

int main(int argc, char const *argv[])
{
    int left[3] = {1,2,3};
    int right[3]= {4,5,6};

    node *T1 = NULL, *T2= NULL;
    
    for(size_t i = 0; i < 3; i++)
    {
        T1 = insert(T1,left[i]);
    }
    
    for(size_t i = 0; i < 3; i++)
    {
        T2 = insert(T2, right[i]);
    }
    
    
    int h1 = T1->height;
    int h2 = T2->height;

    node * new_tree = join(T1, T2);
    display(new_tree);
    printf("Height of the tree is %d\n", height(new_tree));
    
    
    
    return 0;
}
