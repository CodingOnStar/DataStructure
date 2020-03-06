#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#define MinData -10000

typedef int ElementType;
typedef struct HeapStruct *MinHeap;
typedef struct HuffTreeNode *HuffTree;
int A[] = {4,5,3,7,1};
struct HeapStruct
{
    HuffTree *Elements;
    int size;
    int capacity;
};

struct HuffTreeNode{
    int weight;
    HuffTree *left;
    HuffTree *right;
};

HuffTree CreateHuff(); // 初始化哈夫曼树
MinHeap CreateHeap(int MaxSize);
bool isEmpty(MinHeap H);
bool isFull(MinHeap H);
void SortHeap(MinHeap H, ElementType x);
HuffTree DeleteMin(MinHeap H);
HuffTree BuildHuffTree(MinHeap H);
void BuildMinHeap(MinHeap H);
void Insert(HuffTree Huff, MinHeap H);
void Adjust(MinHeap H);

MinHeap CreateHeap(int MaxSize)
{
    HuffTree Huff;
    MinHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = (HuffTree *)malloc((MaxSize + 1) * sizeof(struct HuffTreeNode));
    H->size = 0;
    H->capacity = MaxSize;

    Huff = CreateHuff();
    Huff->weight = MinData;
    H->Elements[0] = Huff;
    return H;
}
// 初始化哈夫曼树
HuffTree CreateHuff()
{
    HuffTree Huff;
    Huff = (HuffTree)malloc(sizeof(struct HuffTreeNode));
    Huff->weight = 0;
    Huff->left = NULL;
    Huff->right = NULL;
    return Huff;
}

bool IsFull(MinHeap H)
{
    return (H->size == H->capacity);
}

bool isEmpty(MinHeap H)
{
    return H->size;
}

void SortHeap(MinHeap H, ElementType x) //因为堆的本质是存在数组中，所以不用新申请空间，下滤
{
    int parent,child, temp;
    temp = H->Elements[x]->weight;                           //提取当前子树父亲结点的值
    for (parent = 1; parent * 2 < H->size; parent = child)
    {
        child = parent * 2;
        if ((child != H->size) && H->Elements[child] > H->Elements[child + 1]) //指针指向左右孩子中较小的一个
            child++;
        if (temp < H->Elements[child]->weight)                          
            break;
        else
        {
            H->Elements[parent] = H->Elements[child];               //当父节点的值大于子结点时，调整他们的位置
        }
    }
    H->Elements[parent]->weight = temp;
}

void Adjust(MinHeap H)
{
    int i;
    for(i = H->size / 2; i > 0; i--)
        SortHeap(H , i);                //按权值的大小调整为最小堆
}

// 建堆
void BuildMinHeap(MinHeap H)
{
    // 将权值读入堆中
    HuffTree Huff;
    for (int i = 0; i < 5; i++) //此处是写定的，实际应该为权值的长度
    {
        Huff = CreateHuff();
        Huff->weight = A[i];
        H->Elements[++H->size] = Huff;
    }
    // 调整堆
    Adjust(H);
}

void Insert(HuffTree Huff, MinHeap H)//上滤
{
    int weight = Huff->weight;
    int i = ++H->size;
    for (; weight > H->Elements[i/2]->weight; i--) {
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = Huff;
}

HuffTree BuildHuffTree(MinHeap H)
{
    HuffTree T;
    int i;
    BuildMinHeap(H);
    for (i = 0; i < H->size;i++)
    {
        T = (HuffTree)malloc(sizeof(struct HuffTreeNode));
        T->left = DeleteMin(H);
        T->right = DeleteMin(H);
        T->weight = T->left->weight + T->right->weight;
        Insert(T, H);
    }
    T = DeleteMin(H);
    return T;
}

HuffTree DeleteMin(MinHeap H)
{
    int parent, child;
    HuffTree temp;
    HuffTree T;
    T = H->Elements[1];
    temp = H->Elements[H->size--];
    for (parent = 1;parent < H->size/2; parent = child) {
        child = parent * 2;
        if((child < H->size) && H->Elements[child]> H->Elements[child + 1])
            child++;
        if (H->Elements[child]->weight >= temp->weight) break;
        else
            H->Elements[parent] = H->Elements[child];
    }
    H->Elements[parent] = temp;
    return T;
}