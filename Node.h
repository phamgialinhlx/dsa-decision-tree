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
#include "CostCalc.h"
#include "BitMask.h"
#include "SplitData.h"
#include <math.h>

using namespace std;

struct Node
{
    Node *left;
    Node *right;

    virtual bool isTerminal() = 0;
    virtual bool compare(Data* data) = 0;
    virtual char getLabel() = 0;

    Node() { left = right = NULL; }
    ~Node() 
    {
        delete left;
        delete right;
    }
};

#endif