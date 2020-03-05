#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef struct TreeNode *BSTree;
struct TreeNode{
    ElementType Data;
    BSTree Left;
    BSTree Right;
};

BSTree FindMIN(BSTree BST)
{
    if (!BST)
        return NULL;
    else if (BST->Left)
        return FindMIN(BST->Left);
    else
        return BST;
}

BSTree iterFind(ElementType X, BSTree BST)
{
    while (BST)
    {
        if (X < BST->Data)
            BST = BST->Left;
        else if (X > BST->Data)
            BST = BST->Right;
        else
            return BST;
    }
    return NULL;
}

BSTree Insert( ElementType X, BSTree BST)
{
    if(!BST)                            //如果树空，直接加入作为根节点
    {
        BST = (BSTree)malloc(sizeof(struct TreeNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }else
    {
        if (X < BST->Data)
            BST->Left = Insert(X, BST->Left); //小于就挂在左边
        else if (X > BST->Data)
            BST->Right = Insert(X, BST->Right); //大于挂在右边
               //相等不做任何事
    }
    return BST;
}

BSTree DeleteNode( ElementType X, BSTree BST)
{
    BSTree tmp;
    if (!BST)
        return NULL;
    else if (X < BST->Data){    
        BST = DeleteNode(X, BST->Left);
    }
    else if (X > BST->Data){ 
        BST = DeleteNode(X, BST->Right);
    }
    else
    {
        if (BST->Left && BST->Right){
            tmp = FindMIN(BST->Right);
            BST->Data = tmp->Data;
            BST->Right = DeleteNode(tmp->Data, BST->Right);
        }else
        {
            tmp = BST;
            if (BST->Left && !BST->Right)
                BST = BST->Left;
            else if (BST->Right && !BST->Left)
                BST = BST->Right;
            else
                BST = NULL;
            free(tmp);
        }
    }
    return BST;
}
void InOrderTree (BSTree BST)
{
    if (BST)
    {
        InOrderTree(BST->Left);
        printf("%d", BST->Data);
        InOrderTree(BST->Right);
    }
}

int main(){
    BSTree BST = NULL;
    BST = Insert(5, BST);
    BST = Insert(7, BST);
    BST = Insert(3, BST);
    BST = Insert(1, BST);
    BST = Insert(2, BST);
    BST = Insert(4, BST);
    BST = Insert(6, BST);
    BST = Insert(8, BST);
    BST = Insert(9, BST);
    InOrderTree(BST);
}