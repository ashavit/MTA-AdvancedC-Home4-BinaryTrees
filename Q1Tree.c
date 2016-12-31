#include <stdlib.h>
#include "Q1Tree.h"

#define MALLOC_ERROR -1

#define NO_NODE_VAL -1

#pragma mark - Private Declarations

static TreeNode* allocateTreeNode(int data);
static void printTreeInorderRec(TreeNode *node);

#pragma mark - Public Implementations

TreeNode* buildTreeRootFromArrayRec(int *arr, int size)
{
    TreeNode *result = NULL;
    if (size == 1)
    {
        if (arr[0] != NO_NODE_VAL)
            result = allocateTreeNode(arr[0]);
    }
    else
    {
        int mid = (size-1) / 2;

        // Make sure node is not -1
        if (arr[mid] != NO_NODE_VAL)
        {
            result = allocateTreeNode(arr[mid]);
            result->left = buildTreeRootFromArrayRec(arr, mid);
            result->right = buildTreeRootFromArrayRec(arr+mid+1, mid);            
        }
    }

    return result;
}

Tree BuildTreeFromArray(int *arr, int  size)
{
    Tree tree;
    tree.root = buildTreeRootFromArrayRec(arr, size);
    return tree;
}

void printTreeInorder(Tree tree)
{
    if (tree.root)
    {
        printTreeInorderRec(tree.root);
        printf("\n");
    }
}

void freeTree(Tree tree)
{

}

#pragma mark - Private Implementations

static TreeNode* allocateTreeNode(int data)
{
    TreeNode *result = (TreeNode*)malloc(sizeof(TreeNode));
    if (!result)
    {
        printf("Malloc error");
        exit(MALLOC_ERROR);
    }

    result->data = data;
    result->left = result->right = NULL;
    return result;
}

void printTreeInorderRec(TreeNode *root)
{
    if (root->left)
    {
        printTreeInorderRec(root->left);
    }

    printf("%d ", root->data);

    if (root->right)
    {
        printTreeInorderRec(root->right);
    }
}
