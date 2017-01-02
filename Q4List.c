#include <stdlib.h>
#include "Q4List.h"

#define MALLOC_ERROR -1

typedef struct _singlyLinkedCell
{
    int data;
    struct _singlyLinkedCell *next;
} SinglyLinkedCell;

typedef struct _singlyLinkedList
{
    SinglyLinkedCell *head;
    SinglyLinkedCell *tail;
    unsigned int size;
} SinglyLinkedList;

typedef struct _levelsLists
{
    unsigned int size;
    SinglyLinkedList **levels;
} LevelsLists;


#pragma mark - Private Declarations

static LevelsLists* allocateLevelsList();
static void freeLevelsList();
static void doubleLevelsListsSize(SinglyLinkedList ***array, unsigned int *size);
static void printLevels(LevelsLists *levelLists);

static SinglyLinkedList* allocateEmptyList();
static void freeList(SinglyLinkedList *list);

static SinglyLinkedCell* allocateListCell(int data);
static void printListCellRec(SinglyLinkedCell *cell);

static void addToEndOfList(SinglyLinkedList *list, SinglyLinkedCell *cell);
static void printList(SinglyLinkedList *list);

void mapTreeByLevelsRec(TreeNode *root, int level, LevelsLists* levels);

#pragma mark - Public Implementations

void printByLevels(Tree tree)
{
    LevelsLists* levels = NULL;
    levels = allocateLevelsList();
    
    if (tree.root)
    {
        mapTreeByLevelsRec(tree.root, 0, levels);
    }
    
    printLevels(levels);
    
    freeLevelsList(levels);
}

#pragma mark - Private Implementations

static LevelsLists* allocateLevelsList()
{
    LevelsLists *ptr = (LevelsLists*)malloc(sizeof(LevelsLists));
    if (!ptr)
    {
        printf("Could not allocate object");
        exit(MALLOC_ERROR);
    }
    
    ptr->levels = NULL;
    ptr->size = 0;
    return ptr;
}

static void freeLevelsList(LevelsLists *levelsLists)
{
    for (int i = 0; i < levelsLists->size; ++i)
    {
        freeList(*(levelsLists->levels+i));
    }
    
    free(levelsLists);
}

static void doubleLevelsListsSize(SinglyLinkedList ***array, unsigned int *size)
{
    unsigned int newSize = (*size * 2) + 1;
    *array = (SinglyLinkedList**)realloc(*array, newSize * sizeof(SinglyLinkedList*));
    if (!array)
    {
        printf("Could not allocate levels array");
        exit(MALLOC_ERROR);
    }
    
    for (int i = *size; i < newSize; ++i)
    {
        (*array)[i] = allocateEmptyList();
    }
    *size = newSize;
}

static void printLevels(LevelsLists *levelLists)
{
    for (int i = 0; i < levelLists->size; ++i)
    {
        printList(*(levelLists->levels + i));
    }
    printf("\n");
}

static SinglyLinkedList* allocateEmptyList()
{
    SinglyLinkedList *list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    if (!list)
    {
        printf("Could not allocate object");
        exit(MALLOC_ERROR);
    }
    
    list->head = list->tail = NULL;
    list->size = 0;
    return list;
}

static void freeList(SinglyLinkedList *list)
{
    SinglyLinkedCell *curr = list->head;
    SinglyLinkedCell *next = NULL;
    while (curr)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    
    list->head = list->tail = NULL;
    free(list);
}

static SinglyLinkedCell* allocateListCell(int data)
{
    SinglyLinkedCell *cell = (SinglyLinkedCell*)malloc(sizeof(SinglyLinkedCell));
    if (!cell)
    {
        printf("Malloc Error");
        exit(-1);
    }
    
    cell->data = data;
    cell->next = NULL;
    return cell;
}

static void addToEmptyList(SinglyLinkedList *list, SinglyLinkedCell *cell)
{
    list->head = list->tail = cell;
}

static void addToEndOfList(SinglyLinkedList *list, SinglyLinkedCell *cell)
{
    list->tail->next = cell;
    list->tail = cell;
}

void addToList(SinglyLinkedList *list, SinglyLinkedCell *cell)
{
    if (!list->head)
        addToEmptyList(list, cell);
    else
        addToEndOfList(list, cell);
}

static void addDataToLevelsArray(LevelsLists* levelsLists, int level, int data)
{
    // Check if we have space
    if (level >= levelsLists->size)
    {
        doubleLevelsListsSize(&(levelsLists->levels), &(levelsLists->size));
    }
    
    addToList(*(levelsLists->levels + level), allocateListCell(data));
}

static void printListCellRec(SinglyLinkedCell *cell)
{
    printf("%d ", cell->data);
    
    if (cell->next)
        printListCellRec(cell->next);
}

static void printList(SinglyLinkedList *list)
{
    if (list->head)
        printListCellRec(list->head);
}

void mapTreeByLevelsRec(TreeNode *root, int level, LevelsLists* levels)
{
    addDataToLevelsArray(levels, level, root->data);
    
    if (root->left)
        mapTreeByLevelsRec(root->left, level + 1, levels);
    
    if (root->right)
        mapTreeByLevelsRec(root->right, level + 1, levels);
}
