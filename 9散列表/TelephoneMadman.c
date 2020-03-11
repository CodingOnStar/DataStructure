#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define KEYLENGTH 11
#define MaxSize 100
#define MaxD 5 //参与计算手机号码的后五位

typedef char ElementType[KEYLENGTH + 1];
typedef int Index;                          //散列地址类型

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
struct HashTbl{
    int TableSize;                          
    List Heads;                             //指向链表头结点的数组
};

//Hash求余
Index Hash(int key, int TableSize)
{
    key = key % TableSize;
    return key;
}
// 查找素数

int NextPrime(int N)
{   //返回大于N且小于MaxSize的最小素数
    int p = (N % 2) ? N + 2 : N + 1; // 从大于 N 的下个奇数开始
    int i;

    while (p <= MaxSize)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) // p 不是素数
                break;
        if (i == 2)  //for循环正常结束，说明P是素数
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

Position Find(ElementType key, HashTable H)
{
    Position P;
    int Pos;
    
    Pos = Hash(atoi(key + KEYLENGTH - MaxD), H->TableSize); //初始散列位置,atoi将char变为int，key指向char的第一个字符
    P = H->Heads[Pos].Next;     //获得链表第一个结点
    while (P != NULL && strcmp(P->Data, key))                //strcmp是比较两个字符串的大小
        P = P->Next;
    return P;
}

bool Insert(HashTable H, ElementType key)
{
    Position P,NewCell;
    Index Pos;

    P = Find(key, H);   //看是否已存在
    if(!P){             //不存在，则插入
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, key);
        NewCell->Count = 1;
        Pos = Hash(atoi(key + KEYLENGTH - MaxD), H->TableSize);
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else
    { //已存在，计数加1
        NewCell->Count++;
        return false;
    }
}

void ScanAndOutput(HashTable H){
    int i,PCnt = 0, MaxCnt = 0; //狂人数和最大通话次数
    ElementType MinPhone;
    List ptr;
    MinPhone[0] = '\0';
    for(i = 0; i <H->TableSize;i++){
        ptr = H->Heads[i].Next;
        while(ptr){
            if(ptr->Count > MaxCnt){                //当前手机号的通话次数大于最大通话次数
                MaxCnt = ptr->Count;
                strcpy(MinPhone, ptr->Data);
                PCnt = 1;
            }
            else if(ptr->Count == MaxCnt){
                PCnt++;
                if(strcmp(MinPhone, ptr->Data) > 0) //当前通话次数和最大通话次数相等，比较电话号码，将较小的更新为MinPhone
                    strcpy(MinPhone, ptr->Data);
            }
            ptr = ptr->Next;
        }
    }
    printf("%s, %d", MinPhone, MaxCnt);
    if(PCnt > 1)printf("%d", PCnt);
    printf("\n");
}

int main(){
    int N,i;
    ElementType key;
    HashTable H;    
    scanf("%d", &N);            //输入的数据个数
    H = CreateTable(N*2);
    for(i = 0; i < N; i++){
        scanf("%s", key);
        Insert(H, key);
        scanf("%s", key);
        Insert(H, key);
    }
    ScanAndOutput(H);
    free(H);
    return 0;
}