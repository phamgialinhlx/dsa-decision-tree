/*
 * This file is part of dsa-decision-tree
 *
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh.
 */

#include "TestGenerator.h"
#include "RandomForest.h"

using namespace std;

int main()
{

    /**
     * g++ -std=c++17 BitMask.cpp Console.cpp CostCalc.cpp Data.cpp DecisionNode.cpp Node.cpp SplitData.cpp TerminalNode.cpp TestGenerator.cpp Tree.cpp RandomForest.cpp Client.cpp -o Client
     * .\Client.exe > outputFromTerminal.txt
     */
    srand(time(NULL));

    int gen;
    cout << "Generate new test? (1 - Yes | 2 - No): ";
    cin >> gen;
    if (gen == 1)
    {
        TestGenerator testGen;
        testGen.generate();
    }

    vector<Data *> *dataset = loadDataSet("train.txt");
    vector<Data *> *valid = loadDataSet("valid.txt");
    vector<Data *> *test = loadDataSet("testNew.txt");
    cout << "\nLoad done!\n";

    // DECISION TREE TEST
    // Tree *tree = new Tree();
    // for (int minSize = 1; minSize < 4; minSize++) {
    //     for (int maxDepth = 2; maxDepth < 8; maxDepth++) {
    //         #include "RandomForest.h"tree->buildTree(dataset, minSize, maxDepth);
    //         cout << "MIN SIZE = " << minSize << endl;
    //         cout << "MAX DEPTH = " << maxDepth << endl;
    //         cout << "Accuracy = " << tree->calcAccuracy(valid) << endl << endl;
    //     }
    // }
    // cout << "Build done!\n";

    // tree->printTree();

    /*
    cout << "========================================================" << endl;
    cout << "RANDOM FOREST TEST" << endl;
    RandomForest *bestForest;
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
    */

    /*
    double bestAcc = 0.0;
    while (bestAcc < 85)
    {
        RandomForest *randomForest = new RandomForest(dataset, valid, 100);
        cout << "\tAccuracy = " << randomForest->calcAccuracy(test) << "%\n\n";
        bestAcc = max(bestAcc, randomForest->calcAccuracy(test));
    }
    cout << "\tBest Accuracy = " << bestAcc;
    */

    int choice;
    cout << "1 - Create a new random forest. \n2 - Load forest from file. \nEnter your choice: ";
    cin >> choice;

    RandomForest *forest = NULL;
    if (choice == 1)
    {
        int method;
        cout << " Enter your method (1 - build best model | 2 - double training): ";
        cin >> method;

        // method - 1
        if (method == 1)
        {
            forest = buildBestModel(dataset, dataset, 100);
            forest->exportToFile("savedData.txt");
        }
        else
        {
            // method - 2
            forest = new RandomForest(dataset, dataset, 100);
            forest->exportToFile("savedData.txt");
        }
    }
    else
    {
        forest = new RandomForest();
        forest->importFromFile("savedData.txt");
    }
    cout << '\n';
    cout << "Accuracy (Valid test) = " << forest->calcAccuracy(valid) << "%\n";
    cout << "Accuracy (Train test) = " << forest->calcAccuracy(dataset) << "%\n";
    cout << "Accuracy (New test) = " << forest->calcAccuracy(test) << "%\n";

    /*
    int choice;
    cout << "1 - Create a new random tree. \n2 - Load a tree from file. \nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        Tree *tree = buildBestModel(dataset, valid);
        cout << "Accuracy = " << tree->calcAccuracy(valid) << "%\n";
        ofstream file("savedData.txt");
        file << tree->getExport();
    }
    else
    {
        ifstream file("savedData.txt");
        string importData;
        while (!file.eof())
        {
            string line;
            getline(file, line);
            importData += line + ' ';
        }
        Tree *tree = new Tree();
        tree->import(importData);
        cout << "Accuracy = " << tree->calcAccuracy(valid) << "%\n";
    }
    */

    return 0;
}