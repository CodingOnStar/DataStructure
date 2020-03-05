/*用静态链表表示二叉树(结构数组)
实际上，结点的信息是放在数组中的，而每个数组的结点包含两个类似链表的指针（实际上为数组的信息）
不需要按照树的顺序存储在数组中，因为分别记录了左右子树的结点，所以具有链表的灵活性。
没有出现的序号即为根
*/
#include <stdlib.h>
#include <stdio.h>
#define Tree int                //视为指针，实际上是int
#define ElementType char
#define Null -1                 //不能返回0，因为0在数组中是下标
#define MaxTree 10

typedef struct BineryTreeNode *BTN;

struct BineryTreeNode
{
    ElementType Element;
    Tree left;
    Tree right;

}T1[MaxTree], T2[MaxTree];
