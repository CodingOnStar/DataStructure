#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
typedef int ElementType;

typedef struct LNode *List;
struct LNode
{
    ElementType Data;
    List Next;
};
struct LNode L;
List PtrL;

//----------------------------------------------------------------
//求链表长度，查找第K个位置，查找，插入，删除

int length(List PtrL)
{
    int j;
    List P = PtrL;
    while (P)
    {
        P = P->Next;
        j++;
    }
    return j;
}
List FindKth(int K, List PtrL)
{
    int i = 1;
    List P = PtrL;
    while (i < K && P != NULL)
    {
        P = P->Next;
        i++;
    }
    if (i == K)
        return P;
    else
        return NULL;
}
List Find(ElementType X, List PtrL)
{
    List P = PtrL;
    while (P != NULL && P->Data != X)
        P = P->Next;
    return P;
}
List insert(ElementType X, int i, List PtrL)
{
    List s, p;
    if (i == 1)                                     //新结点插入在表头
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Next = PtrL;
        s->Data = X;
        return s;
    }
    p = FindKth(i - 1, PtrL);
    if (p == NULL)
    {
        printf("参数i错");
        return NULL;
    }
    else
    {
        p = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }
}

//若想删除第i个结点，因为是单向链表，所以需要先找到第i-1个结点

List delete (int i, List PtrL)
{
    List s, p;
    if (i == 1)
    {
        s = PtrL;
        if (PtrL != NULL)
            PtrL = PtrL->Next;
        else
            return NULL;
        free(s);
        return PtrL;
    }
    p = FindKth(i - 1, PtrL);
    if (p == NULL)
    {
        printf("不存在删除的%d点", i - 1);
        return NULL;
    }
    else if (p->Next == NULL)
    {
        printf("不存在删除的%d点", i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}