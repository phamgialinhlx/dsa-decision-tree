#include "Tree.h"

Tree::Tree()
{
    root = NULL;
}

Tree::~Tree()
{
    /** TODO: delete all Node */
    delete root;
}

/**
 * @brief Building a tree function.
 * 
 * @param dataset The main dataset.
 * @param minSize Minimum Node Records.
 * @param maxDepth Maximum Tree Depth.
 */
void Tree::buildTree(vector<Data *> *dataset, int minSize, int maxDepth)
{
    split(root, dataset, minSize, maxDepth, 1);
    return;
}

void Tree::printTree()
{
    printNode(root, 1);
}

void printNode(Node* node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++) 
        cout << "  ";

    cout << node->toString() << '\n';
    
    printNode(node->left, depth+1);
    printNode(node->right, depth+1);
}