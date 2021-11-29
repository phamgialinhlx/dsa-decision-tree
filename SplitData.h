/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef SPLIT_DATA_H
#define SPLIT_DATA_H

#include "Data.h"
#include "CostCalc.h"
#include "BitMask.h"
#include <math.h>

using namespace std;

namespace SplitData
{
    enum SPLIT_VAL
    {
        ATTRIBUTE = 0,
        COMPARISON,
        COMBINATION,
        SPLIT_TOTAL
    };

    namespace Attribute
    {
        // Compare function
        bool compare(Data* data, int atr, int value)
        {
            return data->attribute.at(atr) == value;
        }

        //Split a dataset based on an attribute and attribute value (equal to atr)
        GroupDataSet *split(DataSet *data, int atr, int value)
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

        //Split a dataset based on an attribute to a group of two new datasets
        //and select the best split point!
        GroupDataSet *getSplit(DataSet *data, int atr)
        {
            GroupDataSet *chosenGroup = NULL;
            double chosenGini = 2.0;
            int chosenValue = -1;
            for (int value = Data::ATT_MIN; value < Data::ATT_MAX; value++)
            {
                GroupDataSet *group = split(data, atr, value);
                double gini = CostCalc::Gini::getGiniIndex(group, data->size());
                if (chosenGini > gini)
                {
                    delete chosenGroup;
                    chosenGroup = group;
                    chosenGini = gini;
                    chosenValue = value;
                }
                else
                {
                    delete group;
                }
            }
            /** TODO: change return type so it can contain chosenValue and gini index */
            return chosenGroup;
        }
    }

    namespace Comparison
    {
        // Compare function
        bool compare(Data* data, int atr, int value)
        {
            return data->attribute.at(atr) < value;
        }

        //Split a dataset based on an attribute and attribute value (less to atr)
        GroupDataSet *split(DataSet *data, int atr, int value)
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

        //Split a dataset based on comparing attribute to a group of two new datasets
        //and select the best split point!
        GroupDataSet *getSplit(DataSet *data, int atr)
        {
            GroupDataSet *chosenGroup = NULL;
            double chosenGini = 2.0;
            int chosenValue = -1;
            for (int value = Data::ATT_MIN; value < Data::ATT_MAX; value++)
            {
                GroupDataSet *group = split(data, atr, value);
                double gini = CostCalc::Gini::getGiniIndex(group, data->size());
                if (chosenGini > gini)
                {
                    delete chosenGroup;
                    chosenGroup = group;
                    chosenGini = gini;
                    chosenValue = value;
                }
                else
                {
                    delete group;
                }
            }
            /** TODO: change return type so it can contain chosenValue and gini index */
            return chosenGroup;
        }
    }

    namespace Combination
    {
        // Compare function
        bool compare(Data* data, int atr, int mask)
        {
            return getBit(mask, data->attribute.at(atr)-1);
        }

        //Split a dataset based on a combination of attribute value
        // mask is the combinatino bit mask of the value
        GroupDataSet *split(DataSet *data, int atr, int mask)
        {
            DataSet *left = new DataSet();
            DataSet *right = new DataSet();
            for (int i = 0; i < data->size(); i++)
            {
                int curAtt = data->at(i)->attribute.at(atr) - 1;
                if (getBit(mask, curAtt))
                    left->push_back(data->at(i));
                else
                    right->push_back(data->at(i));
            }
            GroupDataSet *group = new GroupDataSet(left, right);
            return group;
        }

        //Split a dataset based on a combination of attribute value
        // to a group of two new datasets and select the best split point!
        GroupDataSet *getSplit(DataSet *data, int atr)
        {
            int maskSize = (2 << Data::ATT_SIZE) - 1;
            GroupDataSet *chosenGroup = NULL;
            double chosenGini = 2.0;
            int chosenMask = -1;
            for (int mask = 0; mask < maskSize; mask++)
            {
                GroupDataSet *group = split(data, atr, mask);
                double gini = CostCalc::Gini::getGiniIndex(group, data->size());
                if (chosenGini > gini)
                {
                    delete chosenGroup;
                    chosenGroup = group;
                    chosenGini = gini;
                    chosenMask = mask;
                }
                else
                {
                    delete group;
                }
            }
            /** TODO: change return type so it can contain comMask and gini index */
            return chosenGroup;
        }
    }
}

#endif