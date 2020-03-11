#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#define MinTableSize -100
#define MaxSize 100

typedef int Index;
typedef int ElementType;
typedef Index Position;

typedef enum
{ // 分别对应：有合法元素、空、有已删除元素
    Legitimate,
    Empty,
    Deleted
} EntryType; // 定义单元状态类型

typedef struct HashEntry Cell;
struct HashEntry
{                     //  哈希表存值单元
    ElementType Element; // 存放元素
    EntryType Info;   // 单元状态
};

typedef struct HashTbl *HashTable;
struct HashTbl{
    int TableSize;
    Cell *TheCell;              //哈希表存值单元数组
};
// 查找素数
int NextPrime(int N)
{
    int p = (N % 2) ? N + 2 : N + 1; // 从大于 N 的下个奇数开始
    int i;

    while (p <= MaxSize)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) // p 不是素数
                break;
        if (i == 2)
            break;
        p += 2; // 继续试探下个奇数
    }
    return p;
} 
//建表
HashTable InitialHash(int TableSize)
{
    HashTable H;
    int i;
    if(TableSize < MinTableSize){
        printf("散列表太小");
        return NULL;
    }
    H = (HashTable)malloc(sizeof(struct HashTbl));
    if(H == NULL)
        printf("Failed to allocate");
    H->TableSize = NextPrime(TableSize);        //寻找下一个素数，把这个素数作为TableSize
    H->TheCell = (Cell*)malloc(sizeof(Cell)*H->TableSize);
    if(!H->TheCell)
        printf("Failed to allocate");
    for(i = 0; i < H->TableSize; i++)
        H->TheCell[i].Info = Empty;
        return H;
}

Index Hash(int key, int TableSize){
    key = key % TableSize;
    return key;
}
//双散列
Position Find(ElementType key, HashTable H){
    Position NewPosition, CurPosition;
    int ControversalNum = 0;                    //记录冲突次数
    NewPosition = CurPosition = Hash(key, H->TableSize);
    while(H->TheCell[NewPosition].Info != Empty && H->TheCell[CurPosition].Element != key){
        if(++ControversalNum % 2){
            NewPosition = CurPosition + (ControversalNum + 1) / 2 * (ControversalNum + 1) / 2;
            //di和ControversalNum之间的关系如示
            while(NewPosition >= H->TableSize)
                NewPosition -= H->TableSize;
        }
        else
            NewPosition = CurPosition - ControversalNum / 2 * ControversalNum / 2;
            while(NewPosition < 0)
                NewPosition += H->TableSize;
    }
    return NewPosition;
}

void Insert(HashTable H, ElementType key){
    Position position;
    position = Find(key, H);
    if(H->TheCell[position].Info != Legitimate){        //确认在此插入
        H->TheCell[position].Info = Legitimate;
        H->TheCell[position].Element = key;
    }
}

/*
哈希表：
如果没有出现溢出的情况，那么散列表这种形式的插入、查询、删除的时间复杂度都为O(1)
散列函数的设计需要考虑：
1.效率高，容易计算，转换速率高
2.地址空间均匀分配，减少冲突

数字关键词的散列函数的构造：
1.直接定址法：取key的线性函数为散列函数
2.除留余数法：mod P，一般P取素数
3.数字分析法：分析各个位上的数字情况，选比较随机作为散列地址
4.折叠法：把关键词分割成几个位数相同的部分，然后叠加
5.平法取中法：希望结果能够被每一位影响

4. 冲突处理方法
1. 常用策略
换个位置：开放地址法
同一位置的冲突对象组织在一起：链地址法


1. 开放定址法
一旦产生了冲突（该地址已有其它元素），就按某种规则去寻找另一空地址
若发生了第 i 次冲突，试探的下一个地址将增加 di
基本公式是： (key) = (h(key)+di) mod TableSize （1 ≤ i ≤ TableSize）
决定了不同的解决冲突方案
1). 线性探测
​以增量序列 1,2,…,(TableSize - 1)循环试探下一个存储地址
ASLs:平均查找次数：冲突次数+1=比较次数，即为平均比较次数
ASLu:查不到平均次数：每个位置向后数多少次为空，+1位比较次数，即为平均比较次数
会有聚集现象
2). 平方探测法
​以增量序列循环试探下一个存储地址
缓解了线性探测的聚集现象，但有可能出现找不到存储位置的情况
​如果散列表长度是某个 4k+3（k是正整数）形式的素数时，平方探测法就可以探查到整个散列表空间
3). 双散列
4). 再散列
​当散列表元素太多（即装填因子 α 太大）时，查找效率会下降
​解决的方法是加倍扩大散列表，这个过程就叫"再散列"，扩大时，原有元素需要重新计算放置到新表中
3. 分离链接法
​将相应位置上冲突的所有关键词存储在同一个单链表中
*/

