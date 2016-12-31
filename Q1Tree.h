#ifndef __Q1TREE_H
#define __Q1TREE_H

#include <stdio.h>

typedef struct _treeNode
{
    unsigned int data;
    struct _treeNode *left;
    struct _treeNode *right;
} TreeNode;

typedef struct _tree
{
    TreeNode *root;
} Tree;

Tree BuildTreeFromArray(int  *arr, int  size);
void printTreeInorder(Tree tree); //Print the tree in-order (LDR)
void freeTree(Tree tree);

#endif
