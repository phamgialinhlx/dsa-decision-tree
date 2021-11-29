#include "SplitData.h"

SplitData::GroupSplitData::GroupSplitData(double gini, int atr, int com, SPLIT_VAL met, GroupDataSet* groupData) : 
    giniIndex(gini), attribute(atr), compareValue(com), method(met)
{
    group = groupData;
}

SplitData::GroupSplitData::~GroupSplitData()
{

}

// Compare function
bool SplitData::Attribute::compare(Data *data, int atr, int value)
{
    return data->attribute.at(atr) == value;
}

//Split a dataset based on an attribute and attribute value (equal to atr)
GroupDataSet *SplitData::Attribute::split(DataSet *data, int atr, int value)
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
SplitData::GroupSplitData SplitData::Attribute::getSplit(DataSet *data, int atr)
{
    GroupDataSet *chosenGroup = NULL;
    double chosenGini = 2.0;
    int chosenValue = -1;
    for (int value = Data::ATT_MIN; value < Data::ATT_MAX; value++)
    {
        GroupDataSet *group = SplitData::Attribute::split(data, atr, value);

        DataSet *left = group->first;
        DataSet *right = group->second;

        if (left->empty() || right->empty())
            continue;

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
    return SplitData::GroupSplitData(chosenGini, atr, chosenValue, SplitData::ATTRIBUTE, chosenGroup);
}

// Compare function
bool SplitData::Comparison::compare(Data *data, int atr, int value)
{
    return data->attribute.at(atr) < value;
}

//Split a dataset based on an attribute and attribute value (less to atr)
GroupDataSet *SplitData::Comparison::split(DataSet *data, int atr, int value)
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
SplitData::GroupSplitData SplitData::Comparison::getSplit(DataSet *data, int atr)
{
    GroupDataSet *chosenGroup = NULL;
    double chosenGini = 2.0;
    int chosenValue = -1;
    for (int value = Data::ATT_MIN; value < Data::ATT_MAX; value++)
    {
        GroupDataSet *group = SplitData::Comparison::split(data, atr, value);
        
        DataSet *left = group->first;
        DataSet *right = group->second;

        if (left->empty() || right->empty())
            continue;

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
    return SplitData::GroupSplitData(chosenGini, atr, chosenValue, SplitData::COMPARISON, chosenGroup);
}

// Compare function
bool SplitData::Combination::compare(Data *data, int atr, int mask)
{
    return getBit(mask, data->attribute.at(atr) - 1);
}

//Split a dataset based on a combination of attribute value
// mask is the combinatino bit mask of the value
GroupDataSet *SplitData::Combination::split(DataSet *data, int atr, int mask)
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
SplitData::GroupSplitData SplitData::Combination::getSplit(DataSet *data, int atr)
{
    int maskSize = (2 << Data::ATT_SIZE) - 1;
    GroupDataSet *chosenGroup = NULL;
    double chosenGini = 2.0;
    int chosenMask = -1;
    for (int mask = 0; mask < maskSize; mask++)
    {
        GroupDataSet *group = SplitData::Combination::split(data, atr, mask);
        
        DataSet *left = group->first;
        DataSet *right = group->second;

        if (left->empty() || right->empty())
            continue;

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
    return SplitData::GroupSplitData(chosenGini, atr, chosenMask, SplitData::COMBINATION, chosenGroup);
}