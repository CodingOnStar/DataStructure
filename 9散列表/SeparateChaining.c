#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define KEYLENGTH 11
#define MaxSize 100
#define MaxD 5 //参与计算手机号码的后五位

typedef char ElementType[KEYLENGTH + 1];
typedef int Index; //散列地址类型

typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    int Count;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct HashTbl *HashTable;
struct HashTbl
{
    int TableSize;
    List Heads; //指向链表头结点的数组
};

//Hash求余
Index Hash(int key, int TableSize)
{
    key = key % TableSize;
    return key;
}
// 查找素数

int NextPrime(int N)
{                                    //返回大于N且小于MaxSize的最小素数
    int p = (N % 2) ? N + 2 : N + 1; // 从大于 N 的下个奇数开始
    int i;

    while (p <= MaxSize)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) // p 不是素数
                break;
        if (i == 2) //for循环正常结束，说明P是素数
            break;
        p += 2; // 继续试探下个奇数
    }
    return p;
}

// 创建哈希表
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    for (i = 0; i < H->TableSize; i++)
        H->Heads[i].Next = NULL; // 链表头：H->Heads[i] 是不存东西的
    H->Heads[i].Data[0] = 0;
    H->Heads[i].Count = 0;
    return H;
}

