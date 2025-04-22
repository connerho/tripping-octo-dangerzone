#include <vector>

template<class T>
struct TreeNode
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode() : left(nullptr), right(nullptr) {}
};

enum Order
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER,
    NUM_ORDERS
};

template<class T>
class Tree
{
public:

    Tree(TreeNode<T>* headPtr) : head(headPtr) {}
    ~Tree() {}

    // Depth-First Searches

    // InOrder : Left, Root, Right
    std::vector<T> inOrder()
    {
        std::vector<T> result;
        orderHelper(head, result, IN_ORDER);
        return result;
    }

    // PreOrder : Root, Left, Right
    std::vector<T> preOrder()
    {
        std::vector<T> result;
        orderHelper(head, result, PRE_ORDER);
        return result;
    }

    // PostOrder : Left, Right, Root
    std::vector<T> postOrder()
    {
        std::vector<T> result;
        orderHelper(head, result, POST_ORDER);
        return result;
    }

    //Breadth-First Searches
    std::vector<T> levelOrder()
    {
        std::vector<std::vector<T>> intermediateResult;
        std::vector<T> result;
        
        if(head)
        {
            levelOrderHelper(head, intermediateResult, 0);

            for(int i = 0; i < intermediateResult.size(); ++i)
            {
                for(int j = 0; j < intermediateResult[i].size(); ++j)
                {
                    result.push_back(intermediateResult[i][j]);
                }
            }
        }

        return result;
    }

private:
    TreeNode<T>* head;

    void orderHelper(TreeNode<T>* node, std::vector<T>& inpVector, Order order)
    {
        if(node)
        {
            switch(order)
            {
                default:
                case IN_ORDER:
                    orderHelper(node->left, inpVector, order);
                    inpVector.push_back(node->data);
                    orderHelper(node->right, inpVector, order);
                break;

                case PRE_ORDER:
                    inpVector.push_back(node->data);
                    orderHelper(node->left, inpVector, order);
                    orderHelper(node->right, inpVector, order);
                break;

                case POST_ORDER:
                    orderHelper(node->left, inpVector, order);
                    orderHelper(node->right, inpVector, order);
                    inpVector.push_back(node->data);
                break;
            }
        }
    }

    void levelOrderHelper(TreeNode<T>* node, std::vector<std::vector<T>>& inpVector, int level)
    {
        if(node)
        {
            if(inpVector.size() <= level)
            {
                std::vector<T> newVector;
                inpVector.push_back(newVector);
            }

            inpVector[level].push_back(node->data);
            levelOrderHelper(node->left, inpVector, (level+1));
            levelOrderHelper(node->right, inpVector, (level+1));
        }
    }
};