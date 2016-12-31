#include <stdlib.h>
#include <string.h>
#include "Q2Tree.h"

#define MALLOC_ERROR -1

#pragma mark - Private Declarations

static TreeNode* allocateTreeNode(char data);
static void freeTreeRec(TreeNode *root);
static void printTreeInorderRec(TreeNode *root);
static void removeNewline(char *line);

static BOOL buildExpressionTreeRec(char* str, int size, TreeNode **root);
static double calcExpressionRec(TreeNode *root);

#pragma mark - Public Implementations

BOOL buildExpressionTree(char* str, Tree *tree)
{
    /* Remove last \n char, as input fgets includes new line it as part of string */
    removeNewline(str);
    
    /* Reset tree root before starting */
    tree->root = NULL;
    BOOL result = buildExpressionTreeRec(str, (int)strlen(str), &tree->root);
    return result;
}

double calcExpression(Tree tree)
{
    if (tree.root)
        return calcExpressionRec(tree.root);
    else
        return 0;
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
    if (tree.root)
    {
        freeTreeRec(tree.root);
        tree.root = NULL;
    }
}

#pragma mark - Private Implementations

static TreeNode* allocateTreeNode(char data)
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

static BOOL buildExpressionTreeRec(char* str, int size, TreeNode **root)
{
    printf("str = %s, size = %d\n", str, size);
    // Edge cases:
    if (!size)
        return FALSE;
    
    if (size == 1)
    {
        *root = allocateTreeNode(str[0]);
        return TRUE;
    }
    
    int counter = 0; // Count open brackets
    int i = 0;
    BOOL found = FALSE;
    
    while (i < size && str[i])
    {
        char ch = str[i];
        if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') &&
            counter == 1) // Found an operator for the root node
        {
            found = TRUE;
            break;
        }
        else if (ch == '(')
            ++counter;
        else if (ch == ')')
            --counter;

        ++i;
    }
    
    if (found)
    {
        *root = allocateTreeNode(str[i]);
        
        // Rec calls
        BOOL left = buildExpressionTreeRec(str + 1, i - 1, &((*root)->left));
        BOOL right = buildExpressionTreeRec(str + i + 1, size - i - 2, &((*root)->right));
        return left && right;
    }
    else
    {
        return FALSE;
    }
}

static double calcExpressionRec(TreeNode *root)
{
    // Base case - leaf
    if (!root->left && !root->right)
        return (root->data - '0');
    
    double result = 0;
    double left, right;
    left = right = 0;
    
    if (root->left)
        left = calcExpressionRec(root->left);
    if (root->right)
        right = calcExpressionRec(root->right);
    
    switch (root->data)
    {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
        case '*':
            result = left * right;
            break;
        case '/':
            result = left / right;
            break;
        case '%':
            result = ((int)left % (int)right);
            break;
    }
    
    return result;
}

static void removeNewline(char *line)
{
    size_t len = strlen(line) - 1;
    if (line[len] == '\n')
        line[len] = '\0';
}
