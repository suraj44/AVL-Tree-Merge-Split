#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBTree.cpp"

long long int NUM_VALS;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    clock_t start, stop;
    cout<<"\n\nNote: The number of entries should not exceed the entries in the file\n\n";
    if(argc!=2){
		cout<<"Expected format: ./<exe_file> <number of entries>"<<endl;
		cout<<"Please reenter properly\n";
		exit(0);
	}
    NUM_VALS = (long long int)atoll(argv[1]);

    int *values = (int*)malloc(NUM_VALS * sizeof(int));

    FILE *f = fopen("sorted_dataset.txt", "r");

    RBTree left, right;
    int index = rand() % NUM_VALS;
    printf("Adding values to tree..\n");
    for(int i=0;i< index; i++) {
        fscanf(f, "%d\n", &values[i]);
        // printf("%d ",values[i]);
        left.insertValue(values[i]);
    }

    for(int i= index ;i< NUM_VALS; i++) {
        fscanf(f, "%d\n", &values[i]);
        right.insertValue(values[i]);
    }
    printf("\n");
    printf("------------Inserted values to trees----------\n");

    left.merge(right);

    // left.preorder();
    
    if(left.isRBTreeBlackHeightValid()){
        printf("\nThe merged tree is a valid Red Black Tree\n");
    }

    else {
        printf("\nThe merged tree is a NOT valid Red Black Tree\n");
    }
    // printf("The joined tree is an AVL tree.\n");
    return 0;
}