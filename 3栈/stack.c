#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 10
typedef int ElementType;
int ERROR;

typedef struct SNode *Stack;
struct SNode
{
    ElementType Data[MAXSIZE];
    int top;
};
void Push(ElementType item, Stack PtrS)
{
    if (PtrS->top == MAXSIZE - 1)
    {
        printf("栈已满");
        return;
    }
    else
    {
        PtrS->Data[++(PtrS->top)] = item;
        return;
    }
};
ElementType Pop(Stack PtrS)
{
    if (PtrS->top == -1)
    {
        printf("栈已空");
        return ERROR;
    }
    else
    {
        return PtrS->Data[(PtrS->top)--];
    }
}
