/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef TERMINAL_NODE_H
#define TERMINAL_NODE_H

#include "Data.h"
#include "Node.h"

using namespace std;

struct TerminalNode : virtual Node 
{
    char label;
    TerminalNode() { left = right = NULL; }
    ~TerminalNode() 
    {
        delete left;
        delete right;
    }

    TerminalNode(DataSet* data)
    {
        left = right = NULL;
        vector<int> cnt(Data::LABEL.size(), 0);

        for (int index = 0; index < data->size(); index++)
            for (int label = 0; label < Data::LABEL.size(); label++)
                if (data->at(index)->label == Data::LABEL[label])
                {
                    ++cnt[label];
                    break;
                }
        
        int cur = cnt[0];
        label = Data::LABEL[0];
        for (int index = 0; index < Data::LABEL.size(); index++)
            if (cnt[index] > cur)
            {
                cur = cnt[index];
                label = Data::LABEL[index];
            }
    }

    bool isTerminal()
    {
        return true;
    }

    bool compare(Data* data)
    {
        return true;
    }

    char getLabel()
    {
        return label;
    }
};

#endif