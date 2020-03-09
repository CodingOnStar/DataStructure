#include <stdlib.h>
#include <stdio.h>
#define MaxLength 100
typedef int ElementType;

int A[MaxLength];

void Swap(ElementType A, ElementType B){
    int a;
    a = A;
    A = B;
    B = a;
}
//复杂度:最好情况O(N),最坏情况O(N^2)
//因为只有i严格大于i+1的情况，才做交换，所以冒泡排序稳定
void Bubble_Sort(ElementType A[], int N){
    for(int P = N-1; P >= 0; P--){
        int flag = 0;
        for (int i = 0; i < P; i++){
            if(A[i] > A[i+1]){
                Swap(A[i], A[i + 1]);
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
}
//时间复杂度：最好情况O(N),最坏情况O(N^2)
//也是严格大于，所以插入排序也是稳定的
void Insertion_Sort(ElementType A[], int N){
    for(int P=1; P<N; P++){
        int i;
        int Tmp = A[P];                         //摸下一张牌
        for (i = P;i>0 && A[i-1]>Tmp;i--){
            A[i] = A[i-1];                      //错位
        }
        A[i] = Tmp;
    }
}
//之前两种算法，本质上消除了逆序对的存在，并且每次只消除一个逆序对
//shell排序的想法就是一次交换消除多个逆序对
//时间复杂度：最好最坏都是N^2
void Shell_Sort(ElementType A[], int N){
    int i,Tmp;
    for(int D = N/2;D>0;D/=2){                  //shell排序的大循环
        for(int P=D;P<N;P+=D){                   //插入排序
            Tmp = A[P];
            for (i=P;i>=D && A[i-D]>Tmp;i-=D)
                A[i] = A[i-D];
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

void Selection_Sort(ElementType A[], int N){
    for(int i = 0; i < N; i++){
        int MinPosition = ScanMinPos(A,i,N-1);    //找到i到N-1中最小元的位置，并赋给MinPosition
        Swap(A[i],A[MinPosition]);
    }
}
//缺点是需要额外开一个O(N)的空间
void PercDown(ElementType A[], int i, int N){
    int left = i * 2 + 1;
    int right = i * 2 + 2; 
    int large = i;
    if(left < N && A[left] > A[right])
        large = left;
    if(right < N && A[right] > A[left])
        large = right;
    if(i != large)
        Swap(i, large);
        PercDown(A,large,N);
}

void BuildHeap(ElementType A[], int N){
    for (int i=N/2-1; i>=0; i--)
        PercDown(A,i,N);
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
void HeapSort_Pro(ElementType A[], int N){
    for(int i=N/2;i>=0;i--){
        PercDown(A,i,N);                  //调整为最大堆
    for(int i=N-1;i>0;i--)
        Swap(A[0],A[i]);              //每次将根节点和最后一个节点交换。交换后删除最后一个节点
        PercDown(A,0,i);
    }
}
//有序子序列的归并
//时间复杂度：T(N) = T(N/2) + T(N/2) + O(N) = O(NlogN)。稳定，任何情况下都是这个时间复杂度
//L是数组A要排序的左半部分起始位置，R是右半部分的起始位置，RightEnd是末尾
//虽然时间复杂度比较好，且稳定，但需要额外的数组空间。所以一般不用于内排序，而被用于外排序
//1.递归算法，分而治之
void Merge(ElementType A[], ElementType TmpA[],int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Tmp = L;
    int NumElements = RightEnd - L + 1;
    while(L < LeftEnd && R < RightEnd){
        if(A[L] < A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while(L < LeftEnd)
        TmpA[Tmp++] = A[L++];
    while(R < RightEnd)
        TmpA[Tmp++] = A[R++];
//在TmpA中排好序之后，要放回A中。但因为L的位置已经改变了，所以可以用倒序的方式放回
    for(int i=0; i<NumElements;i++,RightEnd--)
        A[RightEnd] = TmpA[RightEnd];
}

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd){
    int center;
    if(L < RightEnd){
        Msort(A,TmpA,L,center);
        Msort(A,TmpA,center+1,RightEnd);
        Merge(A,TmpA,L,center+1,RightEnd);
    }
}

void Merge_Sort(ElementType A[],int N){
    ElementType *TmpA;
    TmpA = malloc(N * sizeof(ElementType));
    if(TmpA != NULL){
        Msort(A,TmpA,0,N-1);
        free(TmpA);
    }
    else printf("空间不足");
    
}

//2.非递归算法
//两两排序，一直结合。时间复杂度O(logN)，空间复杂度O(N)
void Merge1(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd){
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

void Merge_Pass(ElementType A[], ElementType TmpA[], int N, int length){
    int i, j;
    for (i = 0; i < N-2*length;i +=2*length)
        Merge1(A, TmpA,i,i+length,i+2*length-1);
    if(i + length < N)              //归并到最后两个子序列
        Merge1(A, TmpA,i,i+length,N-1);
    else
        for(j = i; j < N;j++)
            TmpA[j] = A[j];
}

void Merge_Sort_Uncurrent(ElementType A[], int N){
    int length = 1;
    ElementType *TmpA;
    TmpA = malloc(N * sizeof(ElementType));
    if(TmpA != NULL){
        while (length < N)
        {
            Merge_Pass(A, TmpA, N, length);
            length *=2;
            Merge_Pass(TmpA, A, N, length);
            length *=2;
        }
        free(TmpA);
    }
    else printf("空间不足");
}

//QuickSort的关键在于如何选取主元，并且如果根据主元分成两个集合（时间复杂度不能高）
//分而治之
//最好情况：pivot刚好每次选到中间的数，时间复杂度为O(NlogN),空间复杂度O(logN)
//最坏情况：每次选择A[0]，即为T(N)+T(N-1)+...+T(1)=O(N^2),空间复杂度O(N)
//平均情况：时间复杂度O(NlogN),空间复杂度O(logN)
ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Center] < A[Left])
        Swap(A[Left], A[Center]);
    if (A[Left] > A[Right])
        Swap(A[Left], A[Right]);
    if (A[Center] > A[Right])
        Swap(A[Center], A[Right]);
    Swap(A[Center], A[Right - 1]); //把中位数藏到right-1的地方
                                   //因此只需要考虑Left+1到Right-2
    return A[Right - 1];
}
void QuickSort(ElementType A[], int Left, int Right)
{
    int CutOff;
    if (CutOff < Right - Left)
    {
        int pivot = Median3(A, Left, Right);
        int i = Left;
        int j = Right - 1;
        for (;;)
        {
            while (A[++i] <= pivot)
            {
            }
            while (A[--j] >= pivot)
            {
            }
            if (i < j)
                Swap(A[i], A[j]);
            else
                break;
        }
        Swap(A[i], A[Right - 1]);
        QuickSort(A, Left, i - 1);
        QuickSort(A, i + 1, Right);
    }
    else
        Insertion_Sort(A + Left, Right - Left + 1);
}

void Quick_Sort(ElementType A[], int N)
{
    QuickSort(A, 0, N - 1);
}

//基数排序
/*
1.桶排序：当有N个数字需要排成M长度的顺序时,且N>M时，可以采用桶排序
扫描每个数，然后放入响应的桶中，每个桶形成一个链表
时间复杂度：O(N+M)

void Bucket_Sort(ElementType A[], int N){
    int count;
    while(读入一个新的数据)
        将新的数据插入到链表中
    for(int i = 0; i < M; i++){
        if(count[i])
            输出整个链表的值
    }
}

2.基数排序：当M>N时采用本方法。
采用“次位优先”的方法，每次扫描所有的数，先按照个位的大小将N个数分配给各个桶。之后按照十位的大小继续从新分配...直到最高位,
这个过程本质是：分、收、分、收的过程
高位优先为分、分、分...收的过程
时间复杂度：O(P(N+B)),B是桶的个数
*/