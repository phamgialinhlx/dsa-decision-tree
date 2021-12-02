#include "Tree.h"

Tree::Tree()
{
    root = NULL;
}

Tree::Tree(vector<Data *> *dataset, int minSize, int maxDepth) {
    split(root, dataset, minSize, maxDepth, 1);
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

double Tree::calcAccuracy(DataSet *dataset) {
    int count = 0;
    for (int i = 0; i < dataset->size(); i++)
    {   
        if (predict(dataset->at(i))) {
            count++;
        }
    }
    return count * 100.0 / dataset->size();
}

bool Tree::predict(Data *data)
{
    return predict(root, data);
}

bool Tree::predict(Node *node, Data *data)
{
    if (node->compare(data))
    {
        if (node->isTerminal())
        {
            if (node->getLabel() == data->label)
            {
                return true;
            }
            else
                return false;
        }
        else
            predict(node->left, data);
    }
    else
    {
        if (node->isTerminal())
        {
            if (node->getLabel() == data->label)
            {
                return true;
            }
            else
                return false;
        }
        else
            predict(node->right, data);
    }
}

char Tree::predictNode(Data* data) {
    return predictNode(root, data);
}

char Tree::predictNode(Node* node, Data* data) {
    if (node->compare(data))
    {
        if (node->isTerminal())
        {   

            return node->getLabel();        
        }
        else
            predictNode(node->left, data);
    }
    else
    {
        if (node->isTerminal())
        {
            return node->getLabel();    
        }
        else
            predictNode(node->right, data);
    }
}

void printNode(Node *node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++)
        cout << "  ";

    cout << node->toString() << '\n';

    printNode(node->left, depth + 1);
    printNode(node->right, depth + 1);
}