#include <stdlib.h>
#include <stdio.h>
#define MaxLength 100
typedef int ElementType;

int A[MaxLength];

//有序子序列的归并
//时间复杂度：T(N) = T(N/2) + T(N/2) + O(N) = O(NlogN)。稳定，任何情况下都是这个时间复杂度
//L是数组A要排序的左半部分起始位置，R是右半部分的起始位置，RightEnd是末尾
//虽然时间复杂度比较好，且稳定，但需要额外的数组空间。所以一般不用于内排序，而被用于外排序
//1.递归算法，分而治之

void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Tmp = L;
    int NumElements = RightEnd - L + 1;
    while (L < LeftEnd && R < RightEnd)
    {
        if (A[L] < A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while (L < LeftEnd)
        TmpA[Tmp++] = A[L++];
    while (R < RightEnd)
        TmpA[Tmp++] = A[R++];
    //在TmpA中排好序之后，要放回A中。但因为L的位置已经改变了，所以可以用倒序的方式放回
    for (int i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd];
}

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd)
{
    int center;
    if (L < RightEnd)
    {
        Msort(A, TmpA, L, center);
        Msort(A, TmpA, center + 1, RightEnd);
        Merge(A, TmpA, L, center + 1, RightEnd);
    }
}

void Merge_Sort(ElementType A[], int N)
{
    ElementType *TmpA;
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL)
    {
        Msort(A, TmpA, 0, N - 1);
        free(TmpA);
    }
    else
        printf("空间不足");
}

//2.非递归算法
//两两排序，一直结合。时间复杂度O(logN)，空间复杂度O(N)
void Merge1(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Tmp = L;
    int NumElements = RightEnd - L + 1;
    while (L < LeftEnd && R < RightEnd)
    {
        if (A[L] < A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while (L < LeftEnd)
        TmpA[Tmp++] = A[L++];
    while (R < RightEnd)
        TmpA[Tmp++] = A[R++];
}

void Merge_Pass(ElementType A[], ElementType TmpA[], int N, int length)
{
    int i, j;
    for (i = 0; i < N - 2 * length; i += 2 * length)
        Merge1(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N) //归并到最后两个子序列
        Merge1(A, TmpA, i, i + length, N - 1);
    else
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
}

void Merge_Sort_Uncurrent(ElementType A[], int N)
{
    int length = 1;
    ElementType *TmpA;
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL)
    {
        while (length < N)
        {
            Merge_Pass(A, TmpA, N, length);
            length *= 2;
            Merge_Pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else
        printf("空间不足");
}