//邻接矩阵是对称的，所以对于无向图，有一半是被浪费的空间
//用一个大小为（N+1）N/2的数组来存储一般的元素
//Gij在A中对应的下标为[i+(i+1)]/2+j
//邻接表需要N+2E个结点，N代表N个头指针,E代表结点个数，每个结点会出现在两条链中，所以乘以2
//邻接表节约稀疏空间；方便找任一一个邻接点；方便计算入度（对无向图来说）；不方便查找任意一对点是否连接

//以下建立、插入的方式可以参考heaproute
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MaxVertexNum 100
typedef int weightType;
typedef int Vertex;
typedef int DataType;
typedef struct GNode *ptrToGNode;
struct GNode
{           // 图
    int Nv; // 顶点数
    int Ne; // 边数
    weightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum]; // 存顶点的数据
};
typedef ptrToGNode MGraph;

typedef struct ENode *ptrToENode;
struct ENode
{                      // 边
    Vertex V1, V2;     // 有向边<V1,V2>
    weightType Weight; // 权重
};
typedef ptrToENode Edge;

// 初始化图
MGraph Create(int VertexNum)
{
    Vertex v, w;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (v = 0; v < VertexNum; v++)
        for (w = 0; w < VertexNum; w++)
            Graph->G[v][w] = 0;
    return Graph;
}

// 插入边
MGraph Insert(MGraph Graph, Edge E)
{

    // 插入边 <V1,V2>
    Graph->G[E->V1][E->V2] = E->Weight;

    // 如果是无向图，还需要插入边 <V2,V1>
    Graph->G[E->V2][E->V1] = E->Weight;
    return Graph;
}

// 建图
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv); // 读入顶点数
    Graph = Create(Nv);
    scanf("%d", &(Graph->Ne)); // 读入边数
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); // 读入每个边的数据
            Insert(Graph, E);
        }
    }
    return Graph;
}

// 遍历图
void print(MGraph Graph)
{
    Vertex v, w;
    for (v = 0; v < Graph->Nv; v++)
    {
        for (w = 0; w < Graph->Nv; w++)
            printf("%d ", Graph->G[v][w]);
        printf("\n");
    }
}

int main()
{
    MGraph Graph;
    Graph = BuildGraph();
    print(Graph);
    return 0;
}
