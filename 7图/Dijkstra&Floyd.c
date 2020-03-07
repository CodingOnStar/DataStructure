#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../7图/graphSelfmade.h"
#define Inf 1000000
#define Init -1
#define MaxVertex 100
typedef int Vertex;
int G[MaxVertex][MaxVertex];
int dist[MaxVertex];            // Dijskstra距离
int D[MaxVertex][MaxVertex];    //Floyd距离
int path[MaxVertex];            // Dijkstra路径
int PATH[MaxVertex][MaxVertex]; //Floyd路径
int collected[MaxVertex];       // 被收录集合
int Nv;                         // 顶点
int Ne;                         // 边


// 初始化距离和路径信息
void create(Vertex s)
{
    dist[s] = 0;
    collected[s] = true;
    for (int i = 1; i <= Nv; i++)
        if (G[s][i])
        {
            dist[i] = G[s][i];
            path[i] = s;
        }
}

// 查找未收录顶点中dist最小者
Vertex FindMin(Vertex s)
{
    int min = 0; // 之前特地把 dist[0] 初始化为正无穷
    for (Vertex i = 1; i <= Nv; i++)
        if (i != s && dist[i] < dist[min] && !collected[i])
            min = i;
    return min;
}

void Dijkstra(Vertex s)
{
    create(s);
    while (true)
    {
        Vertex V = FindMin(s); // 找到
        if (!V)
            break;
        collected[V] = true; //收录
        for (Vertex W = 1; W <= Nv; W++)
            if (!collected[W] && G[V][W])
            { // 如果未被收录
                if (dist[V] + G[V][W] < dist[W])
                {
                    dist[W] = G[V][W] + dist[V];
                    path[W] = V;
                }
            }
    }
}

bool Floyd(MGraph Graph,WeightType D[][MaxVertexNum], WeightType PATH[][MaxVertexNum])
{
    Vertex i,j,k;
    for (int i = 0; i < Graph->Nv; i++)
        for (int j = 0; j < Graph->Nv; j++)
        {
            D[i][j] = Graph->G[i][j];
            PATH[i][j] = -1;
        }
    for (int k = 0; k < Graph->Nv; k++)
        for (int i = 0; i < Graph->Nv; i++)
            for (int j = 0; j < Graph->Nv; j++)
            {
                if(D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
                    if(i==j && D[i][j]<0)
                        return false;
                    PATH[i][j] = k;
            }
    return true;
}