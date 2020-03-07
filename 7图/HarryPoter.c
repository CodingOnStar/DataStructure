#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../7图/graphSelfmade.h"
#define INFINITY 65535              //设为双字节无符号整数的最大值

bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum])
{
    Vertex i, j, k;
    for (i = 0; i < Graph->Nv; i++)
        for (j = 0; j < Graph->Nv; j++)
            D[i][j] = Graph->G[i][j];

    for (k = 0; k < Graph->Nv; k++)
        for (i = 0; i < Graph->Nv; i++)
            for (j = 0; j < Graph->Nv; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
                if (i == j && D[i][j] < 0)          //发现负值圈
                    return false;
            }
    return true;
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum],Vertex i, int N){
    Vertex j;
    WeightType MaxDist=0;
    for (j=0;j<N;j++){
        if(i!=j && D[i][j]>MaxDist){
            MaxDist = D[i][j];
        }
    }
    return MaxDist;
}

void FindAnimals(MGraph Graph){
    WeightType D[MaxVertexNum][MaxVertexNum],MaxDist,MinDist;
    Vertex animal,i;

    Floyd(Graph,D);
    MinDist = INFINITY;
    for(i=0;i<Graph->Nv;i++){
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        if (MaxDist == INFINITY)
            printf("0\n");
            return;
        if (MaxDist < MinDist)
            MinDist = MaxDist;
            animal = i+1;        //i从0开始，邻接矩阵从第1行开始
    }
    printf("%d,%d", animal, MinDist);
}