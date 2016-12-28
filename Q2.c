
typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define SIZE 100

int main()
{
    char str[SIZE];
    Tree tr;
    double res;
    BOOL expressionOK;
    printf("Please enter the expression: ");
    fgets(str,SIZE,stdin);

    expressionOK = buildExpressionTree(str, &tr);

    if(expressionOK == TRUE)
    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
    {
        printf("The input expression is not valid\n");
        freeTree(tr);
    }

    return 0;
}
