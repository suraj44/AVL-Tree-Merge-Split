# Advanced-Data-Structures


Implementation of an AVL tree and the following functions:
1. join(T1,T2): joins two AVL trees such that all nodes in the left tree are smaller than those in the right tree and it returns an a balanced avl tree containing all nodes of the constituent tree in O(abs(height(T1) - height(T2)))
2. split(T,k): splits an AVL Tree into two smaller AVL trees given a value in the node to split at such that all nodes in the left tree are smaller than k and all values in the right tree are greater than k. Runs in O(height(T))


You can specify the number of input nodes for each program using the following syntax:
## AVL Tree 
### Instructions to run

```
    g++ generator.cpp
    ./a.out <num_of_val_required>
    cd AVL
    gcc avl.c
    ./a.out <same_num_of_vals>
```


```
