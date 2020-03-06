#include <stdlib.h>
#include <stdbool.h>

#define MaxElements 10000

typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct
{
    ElementType *Elements;
    int size;
    int capacity;
};

extern MaxHeap CreateHeap(int MaxSize);
extern bool isEmpty(MaxHeap H);
extern bool isFull(MaxHeap H);
extern void Insert(MaxHeap H, ElementType x);
extern ElementType Delete(MaxHeap H);
extern void PercDown(MaxHeap H, int p);
extern void BuildHeap(MaxHeap H);
