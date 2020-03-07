#include <stdio.h>
#include <stdlib.h>
#define Inf 1000000
#define Init -1
#define MaxVertex 100
typedef int Vertex;
int G[MaxVertex][MaxVertex];
int D[MaxVertex][MaxVertex];    //Floyd距离
int PATH[MaxVertex][MaxVertex]; //Floyd路径
int collected[MaxVertex];       // 被收录集合
int Nv;                         // 顶点
int Ne;                         // 边

extern void Floyd();