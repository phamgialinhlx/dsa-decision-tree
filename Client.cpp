/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "RandomForest.h"
#include "TestGenerator.h"

using namespace std;

int main()
{

    /*
     * g++ -std=c++17 BitMask.cpp Console.cpp CostCalc.cpp Data.cpp DecisionNode.cpp Node.cpp SplitData.cpp TerminalNode.cpp TestGenerator.cpp Tree.cpp RandomForest.cpp Client.cpp -o Client
     */
    srand(time(NULL));

    TestGenerator testGen;
    testGen.generate();

    vector<Data *> *dataset = loadDataSet("train.txt");
    vector<Data *> *valid = loadDataSet("valid.txt");
    cout << "Load done!\n";

    // DECISION TREE TEST
    // Tree *tree = new Tree();
    // for (int minSize = 1; minSize < 4; minSize++) {
    //     for (int maxDepth = 2; maxDepth < 8; maxDepth++) {
    //         tree->buildTree(dataset, minSize, maxDepth);
    //         cout << "MIN SIZE = " << minSize << endl;
    //         cout << "MAX DEPTH = " << maxDepth << endl;
    //         cout << "Accuracy = " << tree->calcAccuracy(valid) << endl << endl;
    //     }
    // }
    //cout << "Build done!\n";

    //tree->printTree();

    cout << "========================================================" << endl;
    cout << "RANDOM FOREST TEST" << endl;
    for (int minSize = 1; minSize <= 3; minSize++)
    {
        for (int maxDepth = 3; maxDepth <= 8; maxDepth++)
        {
            cout << "\tMIN SIZE = " << minSize << endl;
            cout << "\tMAX DEPTH = " << maxDepth << endl;
            RandomForest *randomForest = new RandomForest(dataset, minSize, maxDepth, 100);
            cout << "\tAccuracy = " << randomForest->calcAccuracy(valid) << "%\n\n";
        }
    }
    cout << endl;

    cout << "========================================================" << endl;
    cout << "END" << endl;

    return 0;
}