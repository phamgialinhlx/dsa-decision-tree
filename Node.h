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
using namespace std;

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

// Compute the Entropy index for a plit dataset
// TODO: COMPLETE getEntropyScore() method.
double getEntropyScore(vector<Data *> *data, int atr, vector<int> combination)
{
    int numberOfData = data->size();
    int count[Data::NUMBER_LABELS];
    double result = 0;
    for (int i = 0; i < data->size(); i++)
    {
        for (int j = 0; j < combination.size(); i++)
        {
            if (data->at(i)->attribute.at(atr) == combination[j])
            {
                char label = data->at(i)->label;
                if (label == 'L')
                {
                }
            }
        }
    }
    return result;
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