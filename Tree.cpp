#include "Tree.h"
#include "TerminalNode.h"
#include "DecisionNode.h"

Tree::Tree(bool consoleActivate)
{
    root = NULL;
    console = new Console("Tree", consoleActivate);
}

Tree::Tree(vector<Data *> *dataset, int minSize, int maxDepth, bool consoleActivate)
{
    console = new Console("Tree", consoleActivate);
    buildTree(dataset, minSize, maxDepth);
}

Tree::~Tree()
{
    /** TODO: delete all Node */
    delete root;
    delete console;
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
    console->log(cout, "Buiding tree");
    split(root, dataset, minSize, maxDepth, 1);
    console->log(cout, "done!\n");
    return;
}

void Tree::printTree()
{
    printNode(root, 1);
}

double Tree::calcAccuracy(DataSet *dataset)
{
    int count = 0;
    for (int i = 0; i < dataset->size(); i++)
    {
        if (predict(dataset->at(i)))
        {
            count++;
        }
    }
    return count * 100.0 / dataset->size();
    ;
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

char Tree::predictNode(Data *data)
{
    return predictNode(root, data);
}

char Tree::predictNode(Node *node, Data *data)
{
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

void Tree::import(string importData)
{
    int count;
    stringstream ss(importData);
    ss >> count;

    vector<Node*> nodes;
    nodes.resize(count, NULL);

    for (int index = 0; index < count; index++)
    {
        int isTerminal;
        ss >> isTerminal;
        if (isTerminal)
        {
            char label;
            ss >> label;
            nodes[index] = new TerminalNode(label);
        }
        else
        {
            int attribute;
            int compareValue;
            int method;
            ss >> attribute >> compareValue >> method;
            nodes[index] = new DecisionNode(attribute, compareValue, SplitData::getSplitValue(method));
        }

        int parentCode, direction;
        ss >> parentCode >> direction;
        if (parentCode == -1)
        {
            root = nodes[index];
        }
        else
        {
            if (direction == 0)
            {
                nodes[parentCode]->left = nodes[index];
            }
            else
            {
                nodes[parentCode]->right = nodes[index];
            }
        }
    }
}

string Tree::getExport()
{
    string exportData = "";
    int count = 0;
    
    exportNode(exportData, root, count, -1, -1);

    string line;
    stringstream ss;
    ss << count;
    getline(ss, line);
    exportData = line + '\n' + exportData;

    return exportData;
}

void Tree::exportNode(string& exportData, Node* node, int& count, int parentCode, int direction)
{
    if (node == NULL)
        return;

    node->setCode(count++);

    string line;
    stringstream ss;
    ss << node->getExport() << ' ' << parentCode << ' ' << direction;
    getline(ss, line);
    exportData += line + '\n';

    exportNode(exportData, node->left, count, node->code, 0);
    exportNode(exportData, node->right, count, node->code, 1);
}

Tree *buildBestModel(DataSet *train, DataSet *valid)
{
    Tree *bestModel = NULL;
    double acc = -1.0;
    for (int minSize = 1; minSize <= 3; minSize++)
    {
        for (int maxDepth = 3; maxDepth <= 8; maxDepth++)
        {
            Tree *curModel = new Tree(train, minSize, maxDepth, false);
            double curAcc = curModel->calcAccuracy(valid);
            if (curAcc > acc)
            {
                bestModel = curModel;
                acc = curAcc;
            }
        }
    }
    return bestModel;
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