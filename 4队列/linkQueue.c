#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10
typedef int ElementType;
int ERROR;
/*当使用单链表来存储队列时，单链表的表头可以实现插入和删除，但链表末尾只能实现插入*/

struct Node{
    ElementType Data;
    struct Node *Next;
};
struct QNode{
    struct Node *front;
    struct Node *rear;
};
typedef struct QNode *Queue;
Queue PtrQ;

ElementType DeleteQ(Queue PtrQ)
{
    ElementType Frontitem;
    struct Node *FrontCell;
    if (PtrQ->front == NULL)
    {
        printf("队列已空");
        return ERROR;
    }
    FrontCell = PtrQ->front;
    if ( PtrQ->front == PtrQ->rear)
    {
        PtrQ->front = PtrQ->rear = NULL;
    }
    else
    {
        PtrQ->front = PtrQ->front->Next;
    }
    Frontitem = FrontCell->Data;
    free(FrontCell);
    return Frontitem;
};

void AddQ(Queue PtrQ, ElementType item)
{
    struct Node *node;
    node = (struct Node *)malloc(sizeof(struct Node));
    node->Data = item;
    node->Next = NULL;
    if (PtrQ->rear == NULL)
    { //此时队列空
        PtrQ->rear = node;
        PtrQ->front = node;
    }
    else
    {                         //不为空
        PtrQ->rear->Next = node; // 将结点入队
        PtrQ->rear = node;       // rear 仍然保持最后
    }
}
