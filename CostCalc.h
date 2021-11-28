/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef COST_CALC_H
#define COST_CALC_H

// Headers included
#include "Data.h"
#include <math.h>

/**
 * \brief CostCalc is a namespace that contains functions help us caculate 
 * split node cost!
 */
namespace CostCalc
{
    namespace Gini
    {
        // Compute the Gini Score for a split dataset
        double getGiniScore(DataSet *data, double instances)
        {
            double score = 0.0;
            vector<int> cnt(Data::LABEL.size(), 0);

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
            return (1.0 - score) * ((double)size / instances);
        }

        // Compute the Gini index for a group of split dataset
        double getGiniIndex(GroupDataSet *group, double instances)
        {
            return getGiniScore(group->first, instances) + getGiniScore(group->second, instances);
        }
    }

    namespace Entropy
    {
        // Compute the Gini Score for a split dataset
        double getEntropyScore(DataSet *data)
        {
            int numberOfData = data->size();
            vector<int> count(Data::LABEL.size(), 0);
            double result = 0;
            for (int i = 0; i < numberOfData; i++)
            {
                char label = data->at(i)->label;
                for (int j = 0; j < Data::LABEL.size(); j++)
                {
                    if (label == Data::LABEL.at(j))
                    {
                        count[j]++;
                        break;
                    }
                }
            }
            double entropy = 0.0;
            for (int i = 0; i < Data::LABEL.size(); i++)
            {
                double temp = count[i] * 1.0 / numberOfData;
                if (temp != 0)
                    entropy -= temp * log(temp);
            }
            return entropy;
        }

        // Compute the Entropy index for a group of split dataset
        double getEntropyIndex(GroupDataSet *group, double instances)
        {
            return group->first->size() * getEntropyScore(group->first) / instances + group->second->size() * getEntropyScore(group->second) / instances;
        }
    }
}

#endif