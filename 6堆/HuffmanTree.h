#include <stdbool.h>
typedef int ElementType;
typedef struct HeapStruct *MinHeap;
typedef struct HuffTreeNode *HuffTree;
int A[] = {4, 5, 3, 7, 1};
struct HeapStruct
{
    HuffTree *Elements;
    int size;
    int capacity;
};

struct HuffTreeNode
{
    int weight;
    HuffTree *left;
    HuffTree *right;
};

extern HuffTree CreateHuff(); // 初始化哈夫曼树
extern MinHeap CreateHeap(int MaxSize);
extern bool isEmpty(MinHeap H);
extern bool isFull(MinHeap H);
extern void SortHeap(MinHeap H, ElementType x);
extern HuffTree DeleteMin(MinHeap H);
extern HuffTree BuildHuffTree(MinHeap H);
extern void BuildMinHeap(MinHeap H);
extern void Insert(HuffTree Huff, MinHeap H);
extern void Adjust(MinHeap H);