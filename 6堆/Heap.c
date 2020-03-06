#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#define MaxElements  10000

typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *Elements;
    int size;
    int capacity;
};

MaxHeap CreateHeap(int MaxSize);
bool isEmpty(MaxHeap H);
bool  isFull(MaxHeap H);
void Insert(MaxHeap H, ElementType x);
ElementType Delete(MaxHeap H);

MaxHeap CreateHeap(int MaxSize){
    MaxHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
    H->size = 0;
    H->capacity = MaxSize;
    H->Elements[0] = MaxElements;
    return H;
}
/*----------------------------------------------------------------
int isFull(MaxHeap H){
    if (H->size == H->capacity)
        return 1;
    else return 0;
}
------------------------------------------------------------------*/
   
bool IsFull(MaxHeap H)
{
    return (H->size == H->capacity);
}

bool isEmpty(MaxHeap H)
{
    return H->size;
}

void Insert(MaxHeap H, ElementType x)               //因为堆的本质是存在数组中，所以不用新申请空间
{
    if(IsFull(H)){
        printf("堆已满 \n");
    }else
    {
        int i = ++H->size;
        for(;x > H->Elements[i/2];i/=2){
            H->Elements[i] = H->Elements[i/2];      //做上滤
        H->Elements[i] = x;
        }
    }
}

ElementType Delete(MaxHeap H){
    if (isEmpty(H)){
        printf("堆已空，删除错误");
    }
    int parent,child;
    ElementType temp, MaxItem;
    MaxItem = H->Elements[1];
    temp = H->Elements[H->size--];
    for(parent = 1; parent * 2< H->size; parent = child) {
        child = parent * 2;
        if ((child != H->size) && H->Elements[child] < H->Elements[child+1]) //指针指向左右孩子中较大的一个
            child = child + 1;
        if (temp > H->Elements[child]) break;
        else
        {
            H->Elements[parent] = H->Elements[child];
        }   
    }
    H->Elements[parent] = temp;
    return MaxItem;
}
/*----------- 建造最大堆 -----------*/
void PercDown(MaxHeap H, int p)
{ /* 下滤：将H中以H->Elements[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = H->Elements[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->size) && (H->Elements[Child] < H->Elements[Child + 1]))
            Child++; /* Child指向左右子结点的较大者 */
        if (X >= H->Elements[Child])
            break; /* 找到了合适位置 */
        else       /* 下滤X */
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = X;
}

void BuildHeap(MaxHeap H)
{   /* 调整H->Elements[]中的元素，使满足最大堆的有序性  */
    /* 这里假设所有H->size个元素已经存在H->Elements[]中 */

    int i;

    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->size / 2; i > 0; i--)
        PercDown(H, i);
}
int main()
{
    MaxHeap H;
    int MaxSize = 100;
    H = CreateHeap(MaxSize);
    Insert(H, 55);
    Insert(H, 66);
    Insert(H, 44);
    Insert(H, 33);
    Insert(H, 11);
    Insert(H, 22);
    Insert(H, 88);
    Insert(H, 99);
    /*
		 99
		/  \
	   88  66
	  / \  / \
	 55 11 22 44
	/ 
   33	  
	*/
    Delete(H);
    return 0;
}