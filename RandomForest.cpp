/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "RandomForest.h"

RandomForest::RandomForest()
{
}

RandomForest::RandomForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees)
{
    buildForest(dataset, minSize, maxDepth, numberOfTrees);
}

RandomForest::~RandomForest()
{
    for (int i = forest.size(); i >= 0; i--)
    {
        delete forest.at(i);
    }
}

void RandomForest::buildForest(DataSet *dataset, int minSize, int maxDepth, int numberOfTrees)
{

    int dataSize = dataset->size();

    for (int i = 0; i < numberOfTrees; i++)
    {

        DataSet *bootstrapDataSet = new vector<Data *>();
        for (int j = 0; j < dataset->size(); j++)
        {
            int randomData = rand() % dataSize;
            bootstrapDataSet->push_back(dataset->at(randomData)->clone());
        }
        forest.push_back(new Tree(bootstrapDataSet, minSize, maxDepth));
    }
}

bool RandomForest::predict(Data *data)
{
    vector<int> cnt(Data::LABEL.size(), 0);

    for (int i = 0; i < forest.size(); i++)
    {
        char label = forest.at(i)->predictNode(data);
        for (int j = 0; j < Data::LABEL.size(); j++)
        {
            if (Data::LABEL.at(j) == label)
            {
                cnt[j]++;
                break;
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

double RandomForest::calcAccuracy(DataSet *dataset)
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
