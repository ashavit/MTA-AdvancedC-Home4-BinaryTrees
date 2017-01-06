#include <stdlib.h>
#include "Q3Tree.h"

#define MALLOC_ERROR -1

#define NO_NODE_VAL -1

#pragma mark - Private Declarations

static Tree initTree();
static TreeNode* allocateTreeNode(int data, TreeNode *parent);
static void freeTreeRec(TreeNode *root);
static void printTreeInorderRec(TreeNode *node);

static TreeNode* buildTreeRootFromArrayRec(int *arr, int size, TreeNode *parent, List *leafList);
static TreeNode* findParentRec(TreeNode *root, int parentData, int branchSelect);

static ListNode* allocateListCell(int data);
static void addToEmptyList(List *list, ListNode *cell);
static void addToEndOfList(List *list, ListNode *cell);
static void appendLeafNodeToList(List *list, int data);

#pragma mark - Public Implementations

Tree BuildTreeFromArrayWithLeafList(int *arr, int  size)
{
    Tree tree = initTree();
    tree.root = buildTreeRootFromArrayRec(arr, size, NULL ,&tree.leafList);
    return tree;
}

TreeNode* findParent(Tree tree, int parentData, int branchSelect)
{
    if (tree.root)
        return findParentRec(tree.root, parentData, branchSelect);
    else
        return NULL;
}

Tree AddLeaf(Tree tree, TreeNode *parent, int branchSelect, int data)
{
    // Find leaf cell in list to replace / add
    
    // Add
    TreeNode *newNode = allocateTreeNode(data, parent);
    if (RIGHT == branchSelect)
        parent->right = newNode;
    else
        parent->left = newNode;
    
    return tree;
}

static TreeNode* allocateTreeNode(int data, TreeNode *parent)
{
    TreeNode *result = (TreeNode*)malloc(sizeof(TreeNode));
    if (!result)
    {
        printf("Malloc error");
        exit(MALLOC_ERROR);
    }
    
    result->data = data;
    result->parent = parent;
    result->left = result->right = NULL;
    return result;
}

void printTreeInorder(Tree tree)
{
    if (tree.root)
    {
        printTreeInorderRec(tree.root);
        printf("\n");
    }
}

void printLeafList(Tree tree)
{
    ListNode *cur = tree.leafList.head;
    while (cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void freeTree(Tree tree)
{
    if (tree.root)
    {
        freeTreeRec(tree.root);
        tree.root = NULL;
    }
}

#pragma mark - Private Implementations

static Tree initTree()
{
    Tree tree;
    tree.root = NULL;
    tree.leafList.head = tree.leafList.tail = NULL;
    return tree;
}

static void freeTreeRec(TreeNode *root)
{
    if (root->left)
    {
        freeTreeRec(root->left);
    }
    
    if (root->right)
    {
        freeTreeRec(root->right);
    }
    
    free(root);
}

static void printTreeInorderRec(TreeNode *root)
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

static TreeNode* buildTreeRootFromArrayRec(int *arr, int size, TreeNode *parent, List *leafList)
{
    TreeNode *result = NULL;
    if (size == 1)
    {
        if (arr[0] != NO_NODE_VAL)
            result = allocateTreeNode(arr[0], parent);
    }
    else
    {
        int mid = (size-1) / 2;
        
        // Make sure node is not -1
        if (arr[mid] != NO_NODE_VAL)
        {
            result = allocateTreeNode(arr[mid], parent);
            result->left = buildTreeRootFromArrayRec(arr, mid, result, leafList);
            result->right = buildTreeRootFromArrayRec(arr+mid+1, mid, result, leafList);
        }
    }
    
    // If result is a leaf - save it
    if (result && !result->left && !result->right)
        appendLeafNodeToList(leafList, result->data);
    
    return result;
}

static TreeNode* findParentRec(TreeNode *root, int parentData, int branchSelect)
{
    TreeNode *result = NULL;
    
    // Base Case - root has requested value and no leaf on the required side
    if (root->data == parentData)
    {
        if ((LEFT == branchSelect && !root->left) ||
            (RIGHT == branchSelect && !root->right))
            result = root;
    }
    else
    {
        if (root->left)
            result = findParentRec(root->left, parentData, branchSelect);
        
        // If not found - check right branch
        if (!result && root->right)
            result = findParentRec(root->right, parentData, branchSelect);
    }
    
    return result;
}

#pragma mark Add List Cells

static ListNode* allocateListCell(int data)
{
    ListNode *cell = (ListNode*)malloc(sizeof(ListNode));
    if (!cell)
    {
        printf("Malloc Error");
        exit(-1);
    }
    
    cell->data = data;
    cell->next = NULL;
    return cell;
}

static void addToEmptyList(List *list, ListNode *cell)
{
    list->head = list->tail = cell;
}

static void addToEndOfList(List *list, ListNode *cell)
{
    list->tail->next = cell;
    list->tail = cell;
}

static void appendLeafNodeToList(List *list, int data)
{
    ListNode *newCell = allocateListCell(data);
    
    if (!list->head)
        addToEmptyList(list, newCell);
    else
        addToEndOfList(list, newCell);
}

