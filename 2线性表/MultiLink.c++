/*广义表是线性表的推广
对于线性表而言，n个元素都是基本的单元素；
广义表中这些元素不仅可以是单元素，也可以是另一个广义表 */

#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

typedef struct GNode *GList;
struct GNode{
    int Tag;
    union {
        ElementType Data;
        GList SubList;
    }URegion;
    GList Next;
};