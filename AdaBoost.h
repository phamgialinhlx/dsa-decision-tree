/**
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once

#ifndef ADABOOST_H
#define ADABOOST_H

#include "Data.h"
#include "Stump.h"
#include <vector>

using namespace std;

class AdaBoost
{
private:
    vector<double> sampleWeight;
    vector<Stump *> *stumps;
    DataSet *dataset;

    double calcSignificance(vector<int> errorIndex);

    DataSet *generateNewDataSet(DataSet *dataset);

    void normalizeWeight(double totalWeight);

    double updateNewWeight(vector<int> errorIndex, double significance);

public:
    const double EPSILON = 0.00001;

    AdaBoost(DataSet *dataset);

    AdaBoost(DataSet *dataset, int maxStumps);

    AdaBoost(string fileName);

    // Generate stumps for adaboost
    void generateStumps(int maxStumps);

    // Update weight for each sample
    void updateSampleWeight(vector<int> errorIndex, double significance);

    // Check if prediction is correct
    bool predict(Data *data);

    // Predict for attribute return the label
    char predictNode(vector<int> attribute);

    // Predict for a data return the label
    char predict(Node *node, Data *data);

    // Compute the accuracy of the model
    double calcAccuracy(DataSet *dataset);

    vector<char> guess(string filename);

    //toString method
    string toString();
};
#endif
