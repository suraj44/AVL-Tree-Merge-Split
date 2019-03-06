#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_utils.c"

void check_left(node* root, int value) {
    if(root == NULL){
        return;
    }
    check_left(root->left, value);
    if(root->val > value) {
        printf("There is a node in left tree that is bigger than val!\n");
        exit(1);
    }
    check_left(root->left, value);
}

void check_right(node* root, int value) {
    if(root == NULL){
        return;
    }
    check_right(root->left, value);
    if(root->val < value) {
        printf("There is a node in right tree that is value than val!\n");
        exit(1);
    }
    check_right(root->left, value);
}


int main(int argc, char const *argv[])
{
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

    
    node *T1 = NULL;
    
    for(size_t i = 0; i < 10; i++)
    {
        T1 = insert(T1,values[i]);
    }

    node * dummy = split(T1,index);

    printf("left tree check: ");
    check_left(dummy->left, index);
    printf("No problem\n");

    printf("right tree check:");
    check_right(dummy->right, index);
    printf("No problem\n");
    return 0;
}