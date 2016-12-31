#ifndef __Q2TREE_H
#define __Q2TREE_H

#include <stdio.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct _treeNode
{
    unsigned char data;
    struct _treeNode *left;
    struct _treeNode *right;
} TreeNode;

typedef struct _tree
{
    TreeNode *root;
} Tree;

BOOL buildExpressionTree(char* str, Tree *tree);
double calcExpression(Tree tree);

void printTreeInorder(Tree tree); //Print the tree in-order (LDR)
void freeTree(Tree tree);

#endif
