#include <stdio.h>
#include <stdlib.h>
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
    Vertex V1, V2;
    WeightType weight;
};
typedef ptrtoENode Edge;

extern MGraph CreateGraph(int VertexNum);
extern void InsertGraph(MGraph Graph, Edge E);
extern MGraph BuildGraph();