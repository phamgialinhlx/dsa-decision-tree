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
        double getGiniScore(DataSet *data, double instances);

        // Compute the Gini index for a group of split dataset
        double getGiniIndex(GroupDataSet *group, double instances);
    }

    namespace Entropy
    {
        // Compute the Gini Score for a split dataset
        double getEntropyScore(DataSet *data);

        // Compute the Entropy index for a group of split dataset
        double getEntropyIndex(GroupDataSet *group, double instances);
    }
}

#endif