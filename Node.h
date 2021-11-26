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

// Compute the Gini index for a plit dataset
double getGiniScore(vector<Data *> *data, int atr[])
{
    return 0;
}

// Compute the Entropy index for a plit dataset
// TODO: COMPLETE getEntropyScore() method.
double getEntropyScore(vector<Data *> *data, int atr, vector<int> combination) {
    int numberOfData = data->size();
    int count[Data::NUMBER_LABELS];
    double result = 0;
    for (int i = 0; i < data->size(); i++) {
        for (int j = 0; j < combination.size(); i++) {
            if (data->at(i)->att.at(atr) == combination[j])
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


//Split a dataset based on an attribute and attribute value
vector<Data *> * splitByAttribute(vector<Data *> *data, int atr, int value)
{   
    vector<Data *> *group = new vector<Data*>();
    for (int i = 0; i < data->size(); i++) {
        if (data->at(i)->att.at(atr) == value)
            group->push_back(data->at(i));
    }
    return group;    
}


// Select the best split point for a dataset
pair<vector<Data *>, vector<Data *>> getSplit(vector<Data *> *dataset)
{
    
}

#endif