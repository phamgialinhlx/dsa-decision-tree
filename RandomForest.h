/*
 * This file is part of dsa-decision-tree
 *
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh.
 */

#pragma once
#ifndef RANDOM_FOREST
#define RANDOM_FOREST

#include "Tree.h"
#include "Console.h"

class RandomForest
{
private:
    vector<Tree *> forest;
    Console *console;

public:
    RandomForest(bool consoleActivate = true);

    RandomForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees, bool consoleActivate = true);

    RandomForest(DataSet *dataset, DataSet *valid, int numberOfTrees, bool consoleActivate = true);

    ~RandomForest();

    void buildForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees);

    void buildForest(vector<Data *> *dataset, vector<Data *> *valid, int numberOfTrees);

    double calcAccuracy(DataSet *dataset);

    // Predict the label of the data given.
    bool predict(Data *data);

    char getPredict(Data *data);

    void predictToFile(DataSet *dataset, string filena);

    void importFromFile(string filename);

    void exportToFile(string filename);
};

RandomForest *buildBestModel(DataSet *dataset, DataSet *valid, int numberOfTrees);

#endif