

#define SIZE 100

int main()
{
    int size, i;
    int arr[SIZE];
    Tree tr;

    printf("Please enter the number of items: ");
    scanf("%d", &size);
    for(i=0; i<size; i++)
        scanf("%d", &arr[i]);

    tr = BuildTreeFromArray(arr, size);//the function from question 1

    printByLevels(tr);

    freeTree(tr);
    return 0;
}
