#ifndef AKINATOR_TREE_H

#define AKINATOR_TREE_H

#include <stdio.h>
#include <malloc.h>

#define TREE struct tree


TREE{
    int value;
    TREE * left;
    TREE * right;
};


int search(TREE * T, int cur){
    if (cur == T->value)
        return 1;
    if (T == NULL)
        return 0;
    if (cur > T -> value)
        return search(T-> right, cur);
    return search(T->left, cur);
}


void insert(TREE * T, TREE * cur){
    if (cur -> value > T -> value) {
        if (!T->right)
            T->right = cur;
        else
            insert(T->right, cur);
    }
    else{
        if (!T -> left)
            T ->left = cur;
        else
            insert(T->left, cur);
    }
}


TREE * create(int value){
    TREE * cur;
    cur =(TREE*)malloc(sizeof (TREE));
    cur -> value = value;
    cur -> right = NULL;
    cur -> left = NULL;
    return cur;

}

#endif
