#include "Tree.h"
#include <iostream>

int main()
{
    TreeNode<int> top, left, right, leftleft, leftright;

    // Constructing the values
    top.data = 1;
    left.data = 2;
    right.data = 3;
    leftleft.data = 4;
    leftright.data = 5;

    // Building the tree
    top.left = &left;
    top.right = &right;
    left.left = &leftleft;
    left.right = &leftright;

    Tree<int> myTree(&top);
    std::vector<int> theGoods = myTree.levelOrder();

    for(int i = 0; i < theGoods.size(); ++i)
    {
        std::cout << theGoods[i] << " ";
    }

    return 0;
}