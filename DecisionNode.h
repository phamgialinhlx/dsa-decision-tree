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
#include "SplitData.h"
#include <sstream>
#include "Node.h"

class DecisionNode : virtual public Node
{
    private:
        double giniScore;
        int attribute;
        int compareValue;
        SplitData::SPLIT_VAL method;

    public:
        DecisionNode();
        ~DecisionNode();

        DecisionNode(int atr, int value, SplitData::SPLIT_VAL met);

        bool isTerminal();

        bool compare(Data *data);

        char getLabel();

        string toString();
};

#endif