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
//QuickSort的关键在于如何选取主元，并且如果根据主元分成两个集合（时间复杂度不能高）
//分而治之
//最好情况：pivot刚好每次选到中间的数，时间复杂度为O(NlogN),空间复杂度O(logN)
//最坏情况：每次选择A[0]，即为T(N)+T(N-1)+...+T(1)=O(N^2),空间复杂度O(N)
//平均情况：时间复杂度O(NlogN),空间复杂度O(logN)
ElementType Median3(ElementType A[], int Left, int Right){
    int Center = (Left + Right)/2;
    if(A[Center]<A[Left])
        Swap(A[Left], A[Center]);
    if(A[Left] >A[Right])
        Swap(A[Left], A[Right]);
    if(A[Center]>A[Right])
        Swap(A[Center], A[Right]);
    Swap(A[Center], A[Right-1]);    //把中位数藏到right-1的地方
                                    //因此只需要考虑Left+1到Right-2
    return A[Right-1];
}

void QuickSort (ElementType A[], int Left, int Right){
    int CutOff;
    if(CutOff< Right - Left){
        int pivot = Median3(A,Left,Right);
        int i = Left; int j = Right - 1;
        for(;;){
            while(A[++i]<=pivot){}
            while(A[--j]>=pivot){}
            if(i<j)
                Swap(A[i],A[j]);
            else
                break;
        }
        Swap(A[i],A[Right - 1]);
        QuickSort(A,Left,i-1);
        QuickSort(A,i+1,Right);
    }
    else
        Insertion_Sort (A+Left, Right-Left+1);
}

void Quick_Sort(ElementType A[], int N){
    QuickSort(A,0,N-1);
}