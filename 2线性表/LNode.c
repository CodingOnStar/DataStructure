#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
typedef int ElementType;

typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAX_SIZE];
    int Last;
};
struct LNode L;
List PtrL;

//线性表的四种操作，清空，查找，插入，删除

List MakeEmpty()
{
    List Ptrl;
    Ptrl = (List)malloc(sizeof(struct LNode));
    Ptrl->Last = -1;
    return Ptrl;
}
int Find(ElementType X, List Ptrl)
{
    int i = 0;
    while (i <= Ptrl->Last && Ptrl->Data[i] != X)
        i++;
    if (i > Ptrl->Last)
        return -1;
    else
        return i;
}
void insert(ElementType X, int i, List Ptrl)
{
    int j;
    if (Ptrl->Last == MAX_SIZE - 1)
    {
        printf("表满");
        return;
    }
    if (i < 1 || i > Ptrl->Last + 2)
    {
        printf("位置错误");
        return;
    }
    //第i个位置的下标是i-1
    for (j = Ptrl->Last; j > i - 1; j--)
        Ptrl->Data[j + 1] = Ptrl->Data[j];
    Ptrl->Data[j - 1] = X;
    Ptrl->Last++;
    return;
}

void delete (int i, List Ptrl)
{
    int j;
    if (i < 1 || i > Ptrl->Last + 1)
    {
        printf("不存在第%d个位置", i);
        return;
    }
    for (j = i; j <= Ptrl->Last; j++)
        Ptrl->Data[j - 1] = Ptrl->Data[j];
    Ptrl->Last--;
    return;
}