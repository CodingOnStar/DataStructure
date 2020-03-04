#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10
typedef int ElementType;
int ERROR;

typedef struct DStack *stack;
struct DStack
{
    ElementType Data[MAXSIZE];
    int top1;
    int top2;
};
stack S;

stack CreateStack()
{
    S = (stack)malloc(sizeof(struct DStack));
    S->top1 = -1;
    return S;
}

int IsEmpty()
{
    return S->top1 == -1;
}
/*用数组实现栈，核心是需要实现后进先出的原则
因此将数组的中间一位设为两个栈的底部，将数组的头和尾设为两个栈的top*/

void push(ElementType item, stack ptrl, int Tag)
{
    if (ptrl->top2 - ptrl->top1 == 1)
    {
        printf("栈已满");
        return;
    }
    if (Tag == 1)
    {
        ptrl->Data[++(ptrl->top1)] = item;
    }
    else
    {
        ptrl->Data[ptrl->top2] = item;
    }
}
ElementType pop(stack ptrl, int Tag)
{
    if (Tag == 1)
    {
        if (ptrl->top1 == -1)
        {
            printf("栈已空");
            return ERROR;
        }
        else
            return ptrl->Data[(ptrl->top1)--];
    }
    else
    {
        if (ptrl->top2 == MAXSIZE)
        {
            printf("栈已空");
            return ERROR;
        }
        else
            return ptrl->Data[(ptrl->top2)--];
    }
}