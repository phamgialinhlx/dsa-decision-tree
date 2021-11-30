/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "Tree.h"
#include "TestGenerator.h"

int main()
{

    /*
     * g++ BitMask.cpp CostCalc.cpp Data.cpp DecisionNode.cpp Node.cpp SplitData.cpp TerminalNode.cpp TestGenerator.cpp Tree.cpp Client.cpp -o Client
     */

    TestGenerator testGen;
    testGen.generate();

    vector<Data *> *dataset = loadDataSet("train.txt");
    vector<Data *> * valid = loadDataSet("valid.txt");
    cout << "Load done!\n";

    Tree *tree = new Tree();
    for (int minSize = 1; minSize < 4; minSize++) {
        for (int maxDepth = 2; maxDepth < 8; maxDepth++) {
            tree->buildTree(dataset, minSize, maxDepth);
            cout << "MIN SIZE = " << minSize << endl;
            cout << "MAX DEPTH = " << maxDepth << endl;
            cout << "Accuracy = " << tree->calcAccuracy(valid) << endl << endl;
        }
    }
    //cout << "Build done!\n";

    //tree->printTree();

    cout << "================" << endl;
    cout << "END" << endl;

    return 0;
}