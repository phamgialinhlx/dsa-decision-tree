#include "CostCalc.h"

// Compute the Gini Score for a split dataset
double CostCalc::Gini::getGiniScore(DataSet *data, double instances)
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
double CostCalc::Gini::getGiniIndex(GroupDataSet *group, double instances)
{
    return CostCalc::Gini::getGiniScore(group->first, instances) + CostCalc::Gini::getGiniScore(group->second, instances);
}

// Compute the Gini Score for a split dataset
double CostCalc::Entropy::getEntropyScore(DataSet *data)
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
double CostCalc::Entropy::getEntropyIndex(GroupDataSet *group, double instances)
{
    return group->first->size() * CostCalc::Entropy::getEntropyScore(group->first) / instances 
            + group->second->size() * CostCalc::Entropy::getEntropyScore(group->second) / instances;
}