/*
 * This file is part of dsa-decision-tree
 *
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh.
 */

#include "TestGenerator.h"
#include "AdaBoost.h"
#include "RandomForest.h"

using namespace std;

int main()
{

    /**
     * g++ -std=c++17 AdaBoost.cpp Stump.cpp BitMask.cpp Console.cpp CostCalc.cpp Data.cpp DecisionNode.cpp Node.cpp SplitData.cpp TerminalNode.cpp TestGenerator.cpp Tree.cpp RandomForest.cpp Client.cpp -o Client
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

    vector<Data *> *dataset = loadDataSetBuff("train.txt", 'B', 4);
    vector<Data *> *valid = loadDataSet("valid.txt");
    vector<Data *> *test = loadDataSet("testNew.txt");
    DataSet *private_test = loadDataTest("private_test.txt");
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
    cout << "ADA-BOOST TEST" << endl;
    double bestAccuracy = 0;
    for (int i = 0; i < 400; i++)
    {
        // for (int number = 5; number <= 8; number++)
        // {

            cout << "#" << i << ": ";
            AdaBoost *adaboost = new AdaBoost(dataset, 5);
            cout << adaboost->toString() << endl;
            double accuracy = adaboost->calcAccuracy(valid);
            bestAccuracy = max(bestAccuracy, accuracy);
            cout << "Accuracy = " << accuracy << "%\n\n";
        // }
    }
    cout << "Best accuracy = " << bestAccuracy << "%\n\n";

    // AdaBoost *adaboost = new AdaBoost("bestForAdaBoost.txt");
    // cout << adaboost->toString() << endl;
    // cout << "Accuracy = " << adaboost->calcAccuracy(valid) << "%\n\n";
    // vector<char> guess = adaboost->guess("private_test.txt");
    // for (int i = 0; i < guess.size(); i++)
    // {
    //     cout << guess[i] << " ";
    // }

    cout << "\n========================================================" << endl;
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
        cout << " Enter your method (1 - build best model | 2 - double training | 3 - valid included): ";
        cin >> method;

        int numberOfTrees;
        cout << " Enter your number of trees: ";
        cin >> numberOfTrees;

        // method - 1
        if (method == 1)
        {
            forest = buildBestModel(dataset, dataset, numberOfTrees);
            forest->exportToFile("savedData.txt");
        }
        else
        {
            // method - 2
            if (method == 2)
            {
                forest = new RandomForest(dataset, dataset, numberOfTrees);
                forest->exportToFile("savedData.txt");
            }
            else
            {
                forest = new RandomForest(dataset, valid, numberOfTrees);
                forest->exportToFile("savedData.txt");
            }
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

    cout << '\n';
    forest->predictToFile(private_test, "result.txt");

    cout << "1 - Create a new forest of stumps. \n2 - Load a forests from file. \nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        double bestAccuracy = 0;
        for (int i = 0; i < 100; i++)
        {
            // for (int number = 5; number <= 8; number++)
            // {

            cout << "#" << i << ": ";
            AdaBoost *adaboost = new AdaBoost(dataset, 5);
            cout << adaboost->toString() << endl;
            double accuracy = adaboost->calcAccuracy(valid);
            bestAccuracy = max(bestAccuracy, accuracy);
            cout << "Accuracy = " << accuracy << "%\n\n";
            // }
        }
        cout << "Best accuracy = " << bestAccuracy << "%\n\n";
    }
    else
    {
        AdaBoost *adaboost = new AdaBoost("bestForAdaBoost.txt");
        cout << adaboost->toString() << endl;
        cout << "Accuracy = " << adaboost->calcAccuracy(valid) << "%\n\n";
        vector<char> guess = adaboost->guess("private_test.txt");
        for (int i = 0; i < guess.size(); i++)
        {
            cout << guess[i] << " ";
        }
    }

    cout << "\n========================================================" << endl;
    cout << "END" << endl;

    return 0;
}