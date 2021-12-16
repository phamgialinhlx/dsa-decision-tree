/**
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "AdaBoost.h"
#include "TerminalNode.h"
#include <algorithm>
#include <iostream>
#define M_E		2.7182818284590452354

using namespace std;

AdaBoost::AdaBoost(string fileName)
{
    ifstream file(fileName);
    int attribute;
    int compareValue;
    int method;
    double significance;

    stumps = new vector<Stump *>();

    while (file >> attribute >> compareValue >> method >> significance)
    {
        char left, right;
        file >> left >> right;
        Stump *stump = new Stump(attribute, compareValue, (SplitData::SPLIT_VAL)method, significance);
        stump->left = new TerminalNode(left);
        stump->right = new TerminalNode(right);
        stumps->push_back(stump);
    }
}

AdaBoost::AdaBoost(DataSet *dataset)
{
    int dataSize = dataset->size();
    for (int i = 0; i < dataSize; i++)
    {
        sampleWeight.push_back(1.0 / dataSize);
    }
    stumps = new vector<Stump *>();
}

AdaBoost::AdaBoost(DataSet *dataset, int maxStumps)
{
    int dataSize = dataset->size();
    for (int i = 0; i < dataSize; i++)
    {
        sampleWeight.push_back(1.0 / dataSize);
    }
    stumps = new vector<Stump *>();
    this->dataset = dataset;
    generateStumps(maxStumps);
}

double AdaBoost::updateNewWeight(vector<int> errorIndex, double significance)
{
    double totalWeight = 0;
    sort(errorIndex.begin(), errorIndex.end());
    int j = 0;
    for (int i = 0; i < sampleWeight.size(); i++)
    {
        if (j < errorIndex.size())
            if (errorIndex[j] == i)
            {
                sampleWeight[i] *= pow(M_E, -significance);
                j++;
            }
            else
            {
                sampleWeight[i] *= pow(M_E, significance);
            }
        totalWeight += sampleWeight[i];
    }
    return totalWeight;
}

void AdaBoost::normalizeWeight(double totalWeight)
{
    for (int i = 0; i < sampleWeight.size(); i++)
    {
        sampleWeight[i] = sampleWeight[i] / totalWeight;
    }
}

void AdaBoost::updateSampleWeight(vector<int> errorIndex, double significance)
{
    double totalWeight = updateNewWeight(errorIndex, significance);
    normalizeWeight(totalWeight);
}

double AdaBoost::calcSignificance(vector<int> errorIndex)
{

    double totalError = 0;
    for (int i = 0; i < errorIndex.size(); i++)
    {
        totalError += sampleWeight[i];
    }
    double result = log((1 - totalError + EPSILON) / totalError + EPSILON) / 2.0;
    return result > 1 ? 1 : result;
}

DataSet *AdaBoost::generateNewDataSet(DataSet *dataset)
{
    DataSet *newDataSet = new DataSet();
    for (int i = 0; i < dataset->size(); i++)
    {
        double random = (double)rand() / RAND_MAX;
        double temp = 0;
        for (int j = 0; j < sampleWeight.size(); j++)
        {
            if (temp <= random && random <= temp + sampleWeight[j])
            {
                newDataSet->push_back(dataset->at(j)->clone());
                break;
            }
            else
                temp += sampleWeight[j];
        }
    }
    return newDataSet;
}

void AdaBoost::generateStumps(int maxStumps)
{
    this->dataset = cloneDataSet(dataset);
    for (int i = 0; i < maxStumps; i++)
    {
        //cout << "Generating stump " << i + 1 << " of " << maxStumps << endl;
        SplitData::GroupSplitData tempGroup = getSplit(this->dataset, SplitData::COMBINATION);
        //cout << "\tSplit done!" << endl;
        if (tempGroup.attribute == -1)
            continue;
        // cout << "\tAtrribute: " << tempGroup.attribute << endl;
        // cout << "\tCompare Value: " << tempGroup.compareValue << endl;
        // cout << "\tMethod: " << tempGroup.method << endl;
        DataSet *left = tempGroup.group->first;
        DataSet *right = tempGroup.group->second;
        char leftLabel = toTerminal(left);
        char rightLabel = toTerminal(right);

        // cout << "\tLeft label: " << leftLabel << endl;
        // cout << "\tRight label: " << rightLabel << endl;
        vector<int> errorIndex;
        for (int i = 0; i < left->size(); i++)
        {
            if (left->at(i)->label != leftLabel)
            {
                errorIndex.push_back(i);
            }
        }

        for (int i = 0; i < right->size(); i++)
        {
            if (right->at(i)->label != rightLabel)
            {
                errorIndex.push_back(i);
            }
        }
        // cout << "\tError index size: " << errorIndex.size() << endl;
        double significance = calcSignificance(errorIndex);
        // cout << "\tSignificance: " << significance << endl;
        updateSampleWeight(errorIndex, significance);

        Stump *stump = new Stump(tempGroup.attribute, tempGroup.compareValue, tempGroup.method, significance);
        stump->left = new TerminalNode(leftLabel);
        stump->right = new TerminalNode(rightLabel);
        // cout << "\tStump: " << stump->toString() << endl;
        stumps->push_back(stump);
        this->dataset = generateNewDataSet(this->dataset);
    }
}

bool AdaBoost::predict(Data *data)
{
    vector<double> cnt(Data::LABEL.size(), 0);

    for (int i = 0; i < stumps->size(); i++)
    {
        for (int j = 0; j < Data::LABEL.size(); j++)
        {
            char label = predict(stumps->at(i), data);
            if (label == Data::LABEL[j])
            {
                cnt[j] += stumps->at(i)->getSignificance();
            }
        }
    }

    int iMax = 0;

    for (int i = 0; i < Data::LABEL.size(); i++)
    {
        if (cnt[iMax] < cnt[i])
        {
            iMax = i;
        }
    }
    return Data::LABEL[iMax] == data->label;
}

char AdaBoost::predictNode(vector<int> attribute)
{
    vector<double> cnt(Data::LABEL.size(), 0);

    for (int i = 0; i < stumps->size(); i++)
    {
        for (int j = 0; j < Data::LABEL.size(); j++)
        {
            char label = stumps->at(i)->predict(attribute);
            if (label == Data::LABEL[j])
            {
                cnt[j] += stumps->at(i)->getSignificance();
            }
        }
    }

    int iMax = 0;

    for (int i = 0; i < Data::LABEL.size(); i++)
    {
        if (cnt[iMax] < cnt[i])
        {
            iMax = i;
        }
    }
    return Data::LABEL[iMax];
}

char AdaBoost::predict(Node *node, Data *data)
{
    if (node->compare(data))
    {
        if (node->isTerminal())
        {
            return node->getLabel();
        }
        else
            predict(node->left, data);
    }
    else
    {
        if (node->isTerminal())
        {
            return node->getLabel();
        }
        else
            predict(node->right, data);
    }
}

double AdaBoost::calcAccuracy(DataSet *dataset)
{
    int count = 0;
    for (int i = 0; i < dataset->size(); i++)
    {
        if (predict(dataset->at(i)))
        {
            count++;
        }
    }
    return count * 100.0 / dataset->size();
}

string AdaBoost::toString()
{
    stringstream ss;
    for (int i = 0; i < stumps->size(); i++)
    {
        ss << stumps->at(i)->toString() << endl;
    }
    return ss.str();
}

vector<char> AdaBoost::guess(string filename)
{
    vector<char> result;
    ifstream file(filename);
    string line;
    char semicolon;
    while (file >> line)
    {
        vector<int> attribute;
        stringstream ss(line);
        int num;
        char temp;
        ss >> num;
        attribute.push_back(num);
        while (ss >> temp)
        {
            ss >> num;
            attribute.push_back(num);
        }
        result.push_back(predictNode(attribute));
    }
    return result;
}