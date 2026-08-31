#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

/* Push value into stack */
void push(int value)
{
    stack[++top] = value;
}

/* Pop value from stack */
int pop()
{
    return stack[top--];
}

/* Return precedence */
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

/* Perform operation */
int calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }

    return 0;
}

/* Evaluate expression */
int evaluate(char exp[])
{
    char opStack[MAX];
    int optop = -1;
    int i = 0;

    while (exp[i] != '\0')
    {
        /* Ignore spaces */
        if (exp[i] == ' ')
        {
            i++;
            continue;
        }

        /* Read number */
        if (isdigit(exp[i]))
        {
            int num = 0;

            while (isdigit(exp[i]))
            {
                num = num * 10 + (exp[i] - '0');
                i++;
            }

            push(num);
        }

        /* Opening bracket */
        else if (exp[i] == '(')
        {
            opStack[++optop] = exp[i];
            i++;
        }

        /* Closing bracket */
        else if (exp[i] == ')')
        {
            while (optop >= 0 && opStack[optop] != '(')
            {
                int b = pop();
                int a = pop();
                char op = opStack[optop--];

                push(calculate(a, b, op));
            }

            optop--;       // Remove '('
            i++;
        }

        /* Operator */
        else
        {
            while (optop >= 0 &&
                   opStack[optop] != '(' &&
                   precedence(opStack[optop]) >= precedence(exp[i]))
            {
                int b = pop();
                int a = pop();
                char op = opStack[optop--];

                push(calculate(a, b, op));
            }

            opStack[++optop] = exp[i];
            i++;
        }
    }

    /* Remaining operators */
    while (optop >= 0)
    {
        int b = pop();
        int a = pop();
        char op = opStack[optop--];

        push(calculate(a, b, op));
    }

    return pop();
}

int main(int argc, char *argv[])
{
    
    char expression[MAX] = "";

    if (argc < 2)
    {
        printf("Enter an expression.\n");
        return 1;
    }

    /* Combine command-line arguments */
    for (int i = 1; i < argc; i++)
    {
        strcat(expression, argv[i]);
        strcat(expression, " ");
    }

    printf("%d\n", evaluate(expression));

    return 0;
}
