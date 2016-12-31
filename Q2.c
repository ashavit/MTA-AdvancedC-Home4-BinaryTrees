/* This program accepts a calculation sting for the user, build a calulcation tree and calculates the result */


#include <stdio.h>
#include "Q2Tree.h"

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
        printf("%s = %.2f\n", str, res);
    }
    else
    {
        printf("The input expression is not valid\n");
        freeTree(tr);
    }

    return 0;
}
