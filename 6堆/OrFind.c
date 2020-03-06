#include <stdlib.h>
#include <stdio.h>

#define MaxSize  100
typedef int ElementType;
typedef struct {
    ElementType Data;
    int parent;
}SetType;

//查找给定的元素X所属的集合，用根节点表示。
//当前并查集用二维数组表示，有Data和parent两个数据，并且从0开始计算下标
int Find(SetType S[], ElementType X)
{
    int i;
    for(i=0; i<MaxSize && S[i].Data != X; i++);
    if (i > MaxSize) return -1;
    for(; i >0; i = S[i].parent);
    return i;
}
//将X1和X2所在的两棵树合并
void Union(SetType S[], ElementType X1, ElementType X2)
{
    int root1,root2;
    root1 = Find(S,X1);
    root2 = Find(S,X2);
    if (root1 != root2) S[root1].parent = root2;
}

int FindX(SetType s[], ElementType x)
{
    int i;
    // 找到数组中该值对应的下标
    for (i = 0; i < MaxSize && s[i].Data != x; i++)
        ;
    if (MaxSize <= i) // 如果没有找到，返回 -1
        return -1;
    // 找到该结点的根结点
    for (; s[i].parent >= 0; i = s[i].parent)
        ;
    return i; // 返回根结点在数组 s 中的下标
}