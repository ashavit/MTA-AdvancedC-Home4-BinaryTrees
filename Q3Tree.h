#ifndef __Q3TREE_H
#define __Q3TREE_H

#include <stdio.h>

#define LEFT  0
#define RIGHT 1

typedef struct _listNode
{
    int data;
    struct _listNode* next;
} ListNode;

typedef struct _list
{
    ListNode* head;
    ListNode* tail;
} List;

typedef struct _treeNode
{
    int data;
    struct _treeNode* parent;
    struct _treeNode* left;
    struct _treeNode* right;
} TreeNode;

typedef struct _tree
{
    TreeNode* root;
    List leafList;
} Tree;


Tree BuildTreeFromArrayWithLeafList(int *arr, int size);

TreeNode* findParent(Tree tree, int parentData, int branchSelect);
Tree AddLeaf(Tree tree, TreeNode *parent, int branchSelect, int data);

void printTreeInorder(Tree tree); //Print the tree in-order (LDR)
void printLeafList(Tree tree);
void freeTree(Tree tree);

#endif
