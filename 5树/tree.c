/*在树中，通常使用儿子-兄弟表示法
  即为二叉树
   深度为K的树，最多可以有2的K次方-1个结点
   第i层中，最多有2的i-1次方个结点
    */

#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 10
typedef int ElementType;

typedef struct TreeNode *BinTree;
typedef BinTree Position;

struct TreeNode
{
    ElementType data;
    BinTree left;
    BinTree right;
};

void PreTree (BinTree BT)
{
    if(BT){
        printf("%d",BT->data);
        PreTree(BT->left);
        PreTree(BT->right);
    }
};
//中序和后续遍历同理，以上为递归的方法实现

//********************************
/*以下是中序遍历的非递归实现，利用的方法是堆栈
思路：
没遇到一个结点，就做入栈操作，然后继续遍历其左子树
当然左子树遍历结束之后，从栈顶弹出它并访问
然后继续遍历其右子树*/

void InOrderTraversal(BinTree BT)
{
    BinTree T = BT;
    stack s = CreateStack();
    while (T || !IsEmpty(s))
    {
        while(T)
        {
            Push(s,T);
            T = T->left;
        };
        if ( !IsEmpty(s))
        {
            T = Pop(s);
            printf("%5d", T->data);
            T = T->right;
        }
    }
};
//根据画图的路线，前中后序分别是第一二三次碰到某个结点，然后打印输出
//所以，对于先序遍历的非递归方法，只需要把printf调换到第一次遇到结点即可，即push前

//后序另做思考

//用队列实现层序遍历
void LevelOrderTraversal(BinTree BT)
{
    BinTree T;
    Queue Q;
    if (!BT) return;
    Q = CreateQueue();
    addQueue(Q, BT);
    while(!IsEmptyQ(Q))
    {
        T = deleteQueue(Q);
        printf("%d\n",T->data);
        if (T->left) addQueue(Q, T->left);
        if (T->right) addQueue(Q, T->right);
    }
}

//----------------------------------------------------------------
//输出叶子结点
void FindLeaves(BinTree BT)
{
    if (BT)
    {
        if (!BT->left && !BT->right)
            printf("%d", BT->data); // 打印叶子结点
        FindLeaves(BT->left);       // 进入左子树
        FindLeaves(BT->right);      // 进入右子树
    }
}
//----------------------------------------------------------------
//求树的高度：树的高度为当前子树的高度+1
int GetHeight(BinTree BT)
{
    int hl, hr, maxh;
    if (BT)
    {
        hl = GetHeight(BT->left);  // 求左子树高度
        hr = GetHeight(BT->right); // 求右子树高度
        maxh = (hl > hr) ? hl : hr;
        return maxh + 1; // 当前结点高度为左右子树最大的高度+1
    }
    else
        return 0;
}
