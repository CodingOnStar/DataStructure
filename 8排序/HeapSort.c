#include <stdlib.h>
#include <stdio.h>
#define MaxLength 100
typedef int ElementType;

int A[MaxLength];

void Swap(ElementType A, ElementType B)
{
    int a;
    a = A;
    A = B;
    B = a;
}
//缺点是需要额外开一个O(N)的空间
void PercDown(ElementType A[], int i, int N)
{
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int large = i;
    if (left < N && A[left] > A[right])
        large = left;
    if (right < N && A[right] > A[left])
        large = right;
    if (i != large)
        Swap(i, large);
    PercDown(A, large, N);
}

void BuildHeap(ElementType A[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        PercDown(A, i, N);
}
/*
void Heap_Sort(ElementType A[], int N){
    BuildHeap(A,N);                       //O(N)
    ElementType TmpA[N];
    for(int i=0; i<N; i++)
        TmpA[i] = Delete(A);            //O(logN)
    for(int i=0; i<N; i++)              //O(N)
        A[i] = TmpA[i];
}
*/
//O(NlogN)
void HeapSort_Pro(ElementType A[], int N)
{
    for (int i = N / 2; i >= 0; i--)
    {
        PercDown(A, i, N); //调整为最大堆
        for (int i = N - 1; i > 0; i--)
            Swap(A[0], A[i]); //每次将根节点和最后一个节点交换。交换后删除最后一个节点
        PercDown(A, 0, i);
    }
}