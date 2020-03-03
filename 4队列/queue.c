#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define MAXSIZE 10
typedef int ElementType;
int ERROR;

/*循环队列的解决方法：  1.增加size或者tag标记
                     2.仅使用n-1个空间
front记录的是头元素，rear记录尾元素
设队列的长度为n，则队列中元素个数的情况共有n+1种，rear和front之间的差距有n种
*/

//以下使用的解决办法是2，仅使用n-1个空间
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MAXSIZE];
    int front;
    int rear;
};

Queue CreateQueue();                  // 初始化队列
void AddQ(Queue Q, ElementType item); //  入队
int IsFull(Queue Q);                  // 判断队列是否已满
ElementType DeleteQ(Queue Q);         // 出队
int IsEmpty(Queue Q);                 // 判断队列是否为空

Queue CreateQueue()
{
    Queue PtrQ;
    PtrQ = (Queue)malloc(sizeof(struct QNode));
    PtrQ->front = -1;
    PtrQ->rear = -1;
    return PtrQ;
}

int isFull(Queue PtrQ)
{
    return ((PtrQ->rear + 1) % MAXSIZE == PtrQ->front);
}

int isEmpty(Queue PtrQ)
{
    return (PtrQ->front == PtrQ->rear);
}

void addQueue(Queue PtrQ, ElementType item)
{
    if ((PtrQ->rear + 1) % MAXSIZE == PtrQ->front)
    {
        printf("栈已满");
        return;
    }
    else
    {
        PtrQ->rear = (PtrQ->rear + 1) % MAXSIZE;
        PtrQ->Data[PtrQ->rear] = item;
    }
};
ElementType deleQueue(Queue PtrQ)
{
    if (PtrQ->rear == PtrQ->front)
    {
        printf("栈已空");
        return ERROR;
    }
    else
    {
        PtrQ->front = (PtrQ->front + 1) % MAXSIZE;
        return PtrQ->Data[PtrQ->front];
    }
};