#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef char element;
typedef struct {
    element* data;
    int capacity;
    int top;
}StackType;

void init_stack(StackType* sp)
{
    sp->top = -1;
    sp->capacity = 1;
    sp->data = (element*)malloc(sp->capacity * sizeof(element));
}

int is_empty(StackType* sp)
{
    return (sp->top == -1);
}

int is_full(StackType* sp)
{
    return (sp->top == (MAX_SIZE - 1));
}

void push(StackType* sp, element item)
{
    if (is_full(sp))
    {
        sp->capacity = sp->capacity * 2;
        sp->data = (element*)realloc(sp->data, sp->capacity * sizeof(element));
    }
    sp->data[++(sp->top)] = item;
}

element pop(StackType* sp)
{
    if (is_empty(sp))
    {
        fprintf(stderr, "스택 공백 에러\n");
        return 1;
    }
    else
    {
        return sp->data[(sp->top)--];
    }
}

element peek(StackType* sp)
{
    if (is_empty(sp))
    {
        fprintf(stderr, "스택 공백 에러\n");
        return 1;
    }
    else return sp->data[sp->top];
}

int evaluate_postfix(char exp[])    //후위 표식 계산 함수
{
    StackType sp;
    int len = strlen(exp);
    char ch;
    int op1, op2, value, i = 0;

    init_stack(&sp);

    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
        {
            value = ch - '0';
            push(&sp, value);
        }
        else
        {
            op2 = pop(&sp);
            op1 = pop(&sp);
            switch (ch)
            {
                case '+': push(&sp, op1 + op2); break;
                case '-': push(&sp, op1 - op2); break;
                case '*': push(&sp, op1 * op2); break;
                case '/': push(&sp, op1 / op2); break;
            }
        }
    }
    return pop(&sp);
}

// 후위표기식에 잘못된 문자가 있는지 확인하는 함수
int check_error(char exp[])
{
    int len = strlen(exp);
    for (int i = 0; i < len; i++)
    {
        char ch = exp[i];
        if (ch< '0' || ch > '9')
        {
            if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    char postfix[MAX_SIZE];
    printf("Enter an Postfix expression: ");
    scanf_s("%s", postfix,100);

    if (check_error(postfix)==0)
    {
        printf("Error: Invalid character");
        return 0;
    }

    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}