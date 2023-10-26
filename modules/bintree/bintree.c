#include <stdio.h>
#include "bintree.h"

BinTree NewTree(ElType root, BinTree left_tree, BinTree right_tree){
    BinTree t = newTreeNode(root);
    if(t != NULL){
        LEFT(t) = left_tree;
        RIGHT(t) = right_tree;
    }
    return t;
}