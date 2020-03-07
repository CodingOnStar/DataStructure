#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MaxVertexNum 100
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
typedef struct GNode *ptrtoGNode;
struct GNode
{
    int Nv; //结点数
    int Ne; //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};
typedef ptrtoGNode MGraph;

//结点类型
typedef struct ENode *ptrtoENode;
struct ENode
{
    Vertex V1,V2;
    WeightType weight;
};
typedef ptrtoENode Edge;

MGraph CreateGraph(int VertexNum)
{
    Vertex V,W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = 0;
    return Graph;
}

void InsertGraph(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->weight;
    Graph->G[E->V2][E->V1] = E->weight;
    //因为是无向图，所以要插入到两个方向中
}

MGraph BuildGraph(){
    MGraph Graph;
    int i,Nv;
    Vertex V;
    Edge E;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < Graph->Ne; i++){
            scanf("%d, %d, %d", &E->V1, &E->V2, &E->weight);
            InsertGraph(Graph,E);
        }
    }
    for(V= 0; V < Graph->Nv; V++){
        scanf("%d", &(Graph->Data[V]));
    }
    return Graph;
}
/*
int G[Max][Max], Ne,Nv;
void BuildGraph(){
    int V,W,i,v1,v2,w;
    for (V= 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = 0;
    scanf("%d",&Ne);
    for(i = 0; i < Ne; i++){
        scanf("%d,%d,%d",&v1,&v2,&w);
        G[v1][v2] = w;
        G[v2][v1] = w;
    }
}
*/