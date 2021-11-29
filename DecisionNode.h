/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include "Data.h"
#include "Node.h"
#include "SplitData.h"

using namespace std;

struct DecisionNode : virtual Node 
{
    double giniScore;
    int attribute;
    int compareValue;
    SplitData::SPLIT_VAL method;

    DecisionNode() { left = right = NULL; }
    ~DecisionNode() 
    {
        delete left;
        delete right;
    }

    DecisionNode(int atr, int value, SplitData::SPLIT_VAL met) : attribute(atr), compareValue(value), method(met) { left = right = NULL; }

    bool isTerminal()
    {
        return false;
    }

    bool compare(Data* data)
    {
        switch (method)
        {
        case SplitData::ATTRIBUTE:
            return SplitData::Attribute::compare(data, attribute, compareValue);
        
        case SplitData::COMPARISON:
            return SplitData::Comparison::compare(data, attribute, compareValue);
        
        case SplitData::COMBINATION:
            return SplitData::Combination::compare(data, attribute, compareValue);
        
        default:
            return true;
        }
    }

    char getLabel()
    {
        return ' ';
    }
};

#endif