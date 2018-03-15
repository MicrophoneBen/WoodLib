// main.cpp  通用树的 find() 函数检测
#include <iostream>
#include "GTree.h"
#include "GTreeNode.h"

using namespace std;
using namespace WoodLib;

int main()
{
    GTree<int> t;

    GTreeNode<int> tn;

    t.find(0);     // 结果肯定是一片空白的
    t.find(&tn);   // 因为还没有创建树

    return 0;
}

