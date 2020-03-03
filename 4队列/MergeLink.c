#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10
typedef int ElementType;

/*将两个输入的链表按照非递减的顺序合并成一个链表*/
//----------------------------------------------------------------//

typedef struct PolyNode *PolyNomial;
struct PolyNode
{
    int coef;
    int expo;
    struct PolyNode *link;
};
PolyNomial P1, P2;

int Compare(int a, int b)
{
    if (a > b){
        return 1;
    }
    else if (a < b){
        return -1;
    }
    else
    {
        return 0;
    }
    
};

void Attach(int c, int e, PolyNomial *pRear) //建立新的结点
{
    PolyNomial P;
    P = (PolyNomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expo = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}

PolyNomial PolyAdd(PolyNomial P1, PolyNomial P2)
{
    int sum;
    PolyNomial front,rear,temp; //temp结点用于存放初始的front和rear，最后释放掉
    front = rear;
    rear = (PolyNomial)malloc(sizeof(struct PolyNode));

    while (P1 && P2)
        switch (Compare(P1->expo, P2->expo))
        {
        case 1:
            Attach(P1->coef, P1->expo, &rear);
            P1 = P1->link;
            break;
        case -1:
            Attach(P2->coef, P2->expo, &rear);
            P2 = P2->link;
            break;
        case 0:
            sum = P1->coef + P2->coef;
            Attach(sum, P1->expo, &rear);
            P1 = P1->link;
            P2 = P2->link;
            break;
        }
        //当其中一个链表处理完时，将另一个链表直接依次链接上
        for(;P1;P1 = P1->link)Attach(P1->coef, P1->expo, &rear);
        for(;P2;P2 = P2->link)Attach(P2->coef, P2->expo, &rear);
        rear->link = NULL;
        temp = front;
        front = front->link;
        free(temp);
        return front;
};