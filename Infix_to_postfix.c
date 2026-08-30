#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x)
{
    stack[++top] = x;
}

int pop()
{
    return stack[top--];
}

int calculate(int a, int b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;

    return 0;
}

int evaluate(char expr[])
{
    int i = 0, a, b;
    char op;

    while (expr[i] != '\0')
    {
        // Ignore spaces
        if (expr[i] == ' ')
        {
            i++;
            continue;
        }

        // If number
        if (isdigit(expr[i]))
        {
            push(expr[i] - '0');
        }

        // If opening bracket
        else if (expr[i] == '(')
        {
            // Ignore '('
        }

        // If closing bracket
        else if (expr[i] == ')')
        {
            // Not used in this simple version
        }

        // If operator
        else
        {
            op = expr[i];

            i++;

            while (expr[i] == ' ')
                i++;

            if (isdigit(expr[i]))
            {
                b = expr[i] - '0';
                a = pop();

                push(calculate(a, b, op));
            }
        }

        i++;
    }

    return pop();
}

int main(int argc, char *argv[])
{
    char expression[MAX] = "";

    int i;

    if (argc < 2)
    {
        printf("Enter an expression.\n");
        return 1;
    }

    // Join command-line arguments
    for (i = 1; i < argc; i++)
    {
        strcat(expression, argv[i]);
    }

    printf("Expression: %s\n", expression);
    printf("Result = %d\n", evaluate(expression));

    return 0;
}
