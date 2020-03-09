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
/*
冒泡排序的优点：简单，适用于数组和链表
*/
//复杂度:最好情况O(N),最坏情况O(N^2)
//因为只有i严格大于i+1的情况，才做交换，所以冒泡排序稳定
void Bubble_Sort(ElementType A[], int N)
{
    for (int P = N - 1; P >= 0; P--)
    {
        int flag = 0;
        for (int i = 0; i < P; i++)
        {
            if (A[i] > A[i + 1])
            {
                Swap(A[i], A[i + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}
//时间复杂度：最好情况O(N),最坏情况O(N^2)
//也是严格大于，所以插入排序也是稳定的
void Insertion_Sort(ElementType A[], int N)
{
    for (int P = 1; P < N; P++)
    {
        int i;
        int Tmp = A[P]; //摸下一张牌
        for (i = P; i > 0 && A[i - 1] > Tmp; i--)
        {
            A[i] = A[i - 1]; //错位
        }
        A[i] = Tmp;
    }
}
//之前两种算法，本质上消除了逆序对的存在，并且每次只消除一个逆序对
//shell排序的想法就是一次交换消除多个逆序对
//时间复杂度：最好最坏都是N^2
void Shell_Sort(ElementType A[], int N)
{
    int i, Tmp;
    for (int D = N / 2; D > 0; D /= 2)
    { //shell排序的大循环
        for (int P = D; P < N; P += D)
        { //插入排序
            Tmp = A[P];
            for (i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
        }
        A[i] = Tmp;
    }
}

//选择排序
//时间复杂度最好最坏也是N^2
int ScanMinPos(ElementType A[], int i, int N)
{
    int Min = i;
    int j;
    for (j = i; j <= N; j++)
        if (A[j] < A[Min])
            Min = j;
    return j;
}

void Selection_Sort(ElementType A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        int MinPosition = ScanMinPos(A, i, N - 1); //找到i到N-1中最小元的位置，并赋给MinPosition
        Swap(A[i], A[MinPosition]);
    }
}