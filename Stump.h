/**
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef STUMP_H
#define STUMP_H

#include "Node.h"

class Stump : virtual public Node
{

private:
    double significance;
    int attribute;
    int compareValue;
    SplitData::SPLIT_VAL method;

public:
    Stump(int attribute, int compareValue, SplitData::SPLIT_VAL method, double _significance);
    //is Terminal Node
    bool isTerminal();

    //compare to the data
    bool compare(Data *data);

    //get the significance
    double getSignificance();

    //get the label
    char getLabel();

    //toString method
    string toString();

    //prediction method with attribute return the label predicted
    char predict(vector<int> attribute);

    //check if prediction is correct
    bool predict(Node *node, Data *data);
};

#endif
