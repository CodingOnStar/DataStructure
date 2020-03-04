#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10
typedef int ElementType;
int ERROR;

typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    struct SNode *Next;
};

//利用单向链表实现栈，功能有创建，判断为空，入栈和出栈

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
};
int isEmpty(Stack S)
{
    return (S->Next == NULL);
};

//逆向插入，每次插入时，将新的结点放在头结点上

void Push(ElementType item, Stack S)
{
    struct SNode *temcell;
    temcell = (struct SNode *)malloc(sizeof(struct SNode));
    temcell->Data = item;
    temcell->Next = S->Next;
    S->Next = temcell;
};
//用链表实现的时候，不要判别满不满，用数组实现的时候需要判别
ElementType Pop(Stack S)
{
    struct SNode *firstcell;
    ElementType firstelem;
    if (isEmpty(S)){
        printf("堆栈空");
        return ERROR;
    }
    else
    {
        //头结点S的后一个结点是要pop的结点，
        firstcell = S->Next;
        S->Next = firstcell->Next;
        firstelem = firstcell->Data;
        free(firstcell);
        return firstelem;
    }
}