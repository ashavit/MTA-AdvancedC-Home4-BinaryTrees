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

static ListNode* allocateListNode(int data);
static void addToEmptyList(List *list, ListNode *node);
static void addToEndOfList(List *list, ListNode *node);
static void addInsideList(ListNode *prev, ListNode *node);
static void appendLeafNodeToList(List *list, int data);

static void insertLeafToList(List *list, TreeNode *parent, int branchSelect, int data);
static ListNode* findLeafCellToReplace(List *list, int data);
static ListNode* findLeafCellToInsertAfter(List *list, TreeNode *after);
static TreeNode* findLeafCellToInsertAfterRec(TreeNode *node);
static ListNode* findLeafCellToInsertBefore(List *list, TreeNode *before);
static TreeNode* findLeafCellToInsertBeforeRec(TreeNode *node);

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
    // Add leaf node in list
    insertLeafToList(&tree.leafList, parent, branchSelect, data);
    
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

#pragma mark Add List Nodes

static ListNode* allocateListNode(int data)
{
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node)
    {
        printf("Malloc Error");
        exit(-1);
    }
    
    node->data = data;
    node->next = NULL;
    return node;
}

static void addToEmptyList(List *list, ListNode *node)
{
    list->head = list->tail = node;
}

static void addToBeginningOfList(List *list, ListNode *node)
{
    node->next = list->head;
    list->head = node;
}

static void addToEndOfList(List *list, ListNode *node)
{
    list->tail->next = node;
    list->tail = node;
}

static void addInsideList(ListNode *prev, ListNode *node)
{
    node->next = prev->next;
    prev->next = node;
}

static void appendLeafNodeToList(List *list, int data)
{
    ListNode *newCell = allocateListNode(data);
    
    if (!list->head)
        addToEmptyList(list, newCell);
    else
        addToEndOfList(list, newCell);
}

static void insertLeafToList(List *list, TreeNode *parent, int branchSelect, int data)
{
    ListNode *prevNode = NULL;
    
    // If parent was a leaf - replace his leaf node in list
    if (!parent->left && !parent->right)
    {
        prevNode = findLeafCellToReplace(list, parent->data);
        if (prevNode) /* Make sure value was returned */
            prevNode->data = data;
    }
    else /* parent already has an existing leaf. Need to add a new leaf node */
    {
        ListNode *newNode = allocateListNode(data);
        
        if (!list->head)
            addToEmptyList(list, newNode);
        else
        {
            /* If leaf is added on left, it should be before the leftest descendant of right branch
               If leaf is added on right, it should be after the rightest descendant of left branch */
            prevNode = (LEFT == branchSelect ?
                        findLeafCellToInsertBefore(list, parent->right) :
                        findLeafCellToInsertAfter(list, parent->left));
            
            if (!prevNode)
                addToBeginningOfList(list, newNode);
            else if (prevNode == list->tail)
                addToEndOfList(list, newNode);
            else
                addInsideList(prevNode, newNode);
        }
        
    }
}

static ListNode* findLeafCellToReplace(List *list, int data)
{
    ListNode *cur = list->head;
    while (cur && (cur->data != data))
    {
        cur = cur->next;
    }
    return cur;
}

static ListNode* findLeafCellToInsertBefore(List *list, TreeNode *before)
{
    // Find the data value of before's last descendant (it might not be a leaf itself)
    TreeNode *beforeTreeNode = findLeafCellToInsertBeforeRec(before);

    ListNode *cur = list->head;
    ListNode *prev = NULL;

    while (cur && (cur->data != beforeTreeNode->data))
    {
        prev = cur;
        cur = cur->next;
    }
    return prev;
}

static ListNode* findLeafCellToInsertAfter(List *list, TreeNode *after)
{
    // Find the data value of after's last descendant (it might not be a leaf itself)
    TreeNode *afterTreeNode = findLeafCellToInsertAfterRec(after);
    
    ListNode *cur = list->head;
    while (cur && (cur->data != afterTreeNode->data))
    {
        cur = cur->next;
    }
    return cur;
}

static TreeNode* findLeafCellToInsertBeforeRec(TreeNode *node)
{
    // Base case - node is a leaf
    if (!node->right && !node->left)
        return node;
    else if (node->left) /* Try going left if possible, as we are looking for the most left decendant */
        return findLeafCellToInsertBeforeRec(node->left);
    else
        return findLeafCellToInsertBeforeRec(node->right);
}

static TreeNode* findLeafCellToInsertAfterRec(TreeNode *node)
{
    // Base case - node is a leaf
    if (!node->right && !node->left)
        return node;
    else if (node->right) /* Try going right if possible, as we are looking for the most right decendant */
        return findLeafCellToInsertAfterRec(node->right);
    else
        return findLeafCellToInsertAfterRec(node->left);
}

