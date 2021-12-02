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


class RandomForest
{
private:
    vector<Tree* > forest;    

public:
    RandomForest();

    RandomForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees);

    ~RandomForest();

    void buildForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees);

    double calcAccuracy(DataSet* dataset);

    // Predict the label of the data given.
    bool predict(Data* data);
};

#endif