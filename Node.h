/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef NODE_H
#define NODE_H
#include "Data.h"
#include <math.h>
using namespace std;

//Split a dataset based on an attribute and attribute value
vector<Data *> * splitByAttribute(vector<Data *> *data, int atr, int value);

struct Node
{
    double giniScore;
    int attribute;

    Node *left;
    Node *right;
};

// Compute the Gini Score for a split dataset
double getGiniScore(DataSet *data, double instances)
{
    double score = 0.0;
    vector<int> cnt;
    cnt.resize(Data::LABEL.size(), 0);

    for (int index = 0; index < data->size(); index++)
        for (int label = 0; label < Data::LABEL.size(); label++)
            if (data->at(index)->label == Data::LABEL[label])
            {
                ++cnt[label];
                break;
            }

    int size = 0;
    for (int label = 0; label < Data::LABEL.size(); label++)
        size += cnt[label];

    if (size == 0)
        return 0.0;

    for (int label = 0; label < Data::LABEL.size(); label++)
    {
        double proportion = (double)cnt[label] / size;
        score += proportion * proportion;
    }
    return (1.0 - score) / ((double)size / instances);
}

// Compute the Gini index for a group of split dataset
double getGiniIndex(GroupDataSet *group, double instances)
{
    return getGiniScore(group->first, instances) + getGiniScore(group->second, instances);
}

double getEntropyScore(DataSet *data) {
    int numberOfData = data->size();
    vector<int> count(Data::LABEL.size(), 0);
    double result = 0;
    for (int i = 0; i < numberOfData; i++) {
        char label = data->at(i)->label;
        for (int j = 0; j < Data::LABEL.size(); j++)
        {
            if (label == Data::LABEL.at(j)) {
                count[j]++;
                break;
            }
        }
    }
    double entropy = 0.0;
    for (int i = 0; i < Data::LABEL.size(); i++) {
        double temp = count[i] * 1.0 / numberOfData;
        if (temp != 0) entropy -= temp*log(temp);
    }
    return entropy;
}

// Compute the Entropy index for a plit dataset
double getEntropyIndex(GroupDataSet *group, double instances) {
    return group->first->size() * getEntropyScore(group->first) / instances
         + group->second->size() * getEntropyScore(group->second) / instances;
}


//Split a dataset based on an attribute and attribute value (equal to atr)
GroupDataSet *splitByAttributeEqual(DataSet *data, int atr, int value)
{
    DataSet *left = new DataSet();
    DataSet *right = new DataSet();
    for (int i = 0; i < data->size(); i++)
    {
        if (data->at(i)->attribute.at(atr) == value)
            left->push_back(data->at(i));
        else
            right->push_back(data->at(i));
    }
    GroupDataSet *group = new GroupDataSet(left, right);
    return group;
}

//Split a dataset based on an attribute and attribute value (less to atr)
GroupDataSet *splitByAttributeCompare(DataSet *data, int atr, int value)
{
    DataSet *left = new DataSet();
    DataSet *right = new DataSet();
    for (int i = 0; i < data->size(); i++)
    {
        if (data->at(i)->attribute.at(atr) < value)
            left->push_back(data->at(i));
        else
            right->push_back(data->at(i));
    }
    GroupDataSet *group = new GroupDataSet(left, right);
    return group;
}

// Select the best split point for a data
GroupDataSet *getSplit(DataSet *data)
{
    int instances = data->size();
}

#endif