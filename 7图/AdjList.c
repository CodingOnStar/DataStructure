#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MaxVertexNum 100
typedef int WeightType;
typedef int DataType;
typedef int Vertex;

typedef struct ENode *ptrtoENode;
struct ENode
{
    Vertex V1, V2;
    WeightType weight;
};
typedef ptrtoENode Edge;

typedef struct GNode *ptrtoGNode;
typedef struct AdjVNode *ptrtoVnode;
struct AdjVNode
{
    Vertex AdjV;        //邻接点下标
    WeightType weight;  //权重
    ptrtoVnode Next;    //指向下一个邻接点的指针
};

typedef struct Vnode    //头结点
{
    ptrtoVnode FirstEdge;   //头结点包含的指向第一个结点的指针
    DataType Data;          
} AdjList[MaxVertexNum];    //AdjList是邻接表的类型（头结点有几个，数组就有多长）

struct GNode
{
    int Nv; //顶点数
    int Ne; //边数
    AdjList G;//邻接表
};
typedef ptrtoGNode LGraph;  //以邻接表的方式存储图类型

LGraph CreateLGraph(int VertexNum){
    Vertex V,W;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V =0;V<Graph->Nv;V++){
        Graph->G[V].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph,Edge E){
    ptrtoVnode NewNode;
    NewNode = (ptrtoVnode)malloc(sizeof(struct Vnode));
    NewNode->AdjV = E->V2;
    NewNode->weight = E->weight;
    //插入V1的表头
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    //若是无向图，则将V1和V2反过来再插入一次即可
    NewNode = (ptrtoVnode)malloc(sizeof(struct Vnode));
    NewNode->AdjV = E->V1;
    NewNode->weight = E->weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
