#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_utils.c"

void check_bf(node* root) {
    if(root == NULL){
        return;
    }
    check_bf(root->left);
    printf("%d ", balance_factor(root));
    if(balance_factor(root) > 1 || balance_factor(root) < -1) {
        printf("There is an unbalanced node in the tree!\n");
        exit(1);
    }
    check_bf(root->left);
}



int main(int argc, char const *argv[])
{
    srand(time(NULL));
    clock_t start, stop;
    NUM_VALS = (long long int)atoll(argv[1]);

    int *values = (int*)malloc(NUM_VALS * sizeof(int));

    FILE *f = fopen("sorted_dataset.txt", "r");

    node * left = NULL, *right = NULL;
    int index = rand() % NUM_VALS;
    printf("Adding values to tree..\n");
    for(int i=0;i< index; i++) {
        fscanf(f, "%d\n", &values[i]);
        // printf("%d ",values[i]);
        left = insert(left,values[i]);
    }

    for(int i= index ;i< NUM_VALS; i++) {
        fscanf(f, "%d\n", &values[i]);
        right = insert(right,values[i]);
    }
    printf("\n");

    node * joined = join(left,right);
    printf("%d %d\n", height(left), height(right));

    check_bf(joined);
    printf("The joined tree is an AVL tree.\n");
    printf("%d\n", height(joined));
    return 0;
}