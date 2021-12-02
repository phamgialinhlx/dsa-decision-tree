/*
 * This file is part of dsa-decision-tree
 *
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh.
 */

#include "RandomForest.h"

RandomForest::RandomForest(bool consoleActivate)
{
    console = new Console("Forest", consoleActivate);
}

RandomForest::RandomForest(vector<Data *> *dataset, int minSize, int maxDepth, int numberOfTrees, bool consoleActivate)
{
    console = new Console("Forest", consoleActivate);
    buildForest(dataset, minSize, maxDepth, numberOfTrees);
}

RandomForest::RandomForest(DataSet *dataset, DataSet *valid, int numberOfTrees, bool consoleActivate)
{
    console = new Console("Forest", consoleActivate);
    buildForest(dataset, valid, numberOfTrees);
}

RandomForest::~RandomForest()
{
    for (int i = forest.size(); i >= 0; i--)
    {
        delete forest.at(i);
    }
    delete console;
}

void RandomForest::buildForest(DataSet *dataset, int minSize, int maxDepth, int numberOfTrees)
{
    console->log(cout, "Build forrest. . .");
    int dataSize = dataset->size();

    for (int i = 0; i < numberOfTrees; i++)
    {
        DataSet *bootstrapDataSet = new vector<Data *>();
        for (int j = 0; j < dataset->size(); j++)
        {
            int randomData = rand() % dataSize;
            int cloneTime = 1;
            if (dataset->at(randomData)->label == 'B')
                cloneTime = 4;
            for (int clone = 0; clone < cloneTime; clone++)
                bootstrapDataSet->push_back(dataset->at(randomData)->clone());
        }
        forest.push_back(new Tree(bootstrapDataSet, minSize, maxDepth, false));
    }
    console->log(cout, "done!");
}

void RandomForest::buildForest(vector<Data *> *dataset, vector<Data *> *valid, int numberOfTrees)
{
    console->log(cout, "Build forrest. . .");
    int dataSize = dataset->size();

    for (int i = 0; i < numberOfTrees; i++)
    {
        DataSet *bootstrapDataSet = new vector<Data *>();
        for (int j = 0; j < dataset->size(); j++)
        {
            int randomData = rand() % dataSize;
            int cloneTime = 1;
            if (dataset->at(randomData)->label == 'B')
                cloneTime = 4;
            for (int clone = 0; clone < cloneTime; clone++)
                bootstrapDataSet->push_back(dataset->at(randomData)->clone());
        }
        forest.push_back(buildBestModel(bootstrapDataSet, valid));
    }
    console->log(cout, "done!");
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

char RandomForest::getPredict(Data *data)
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
    return Data::LABEL[iMax];
}

void RandomForest::predictToFile(DataSet* dataset, string filename)
{
    ofstream file(filename);

    for (int i = 0; i < dataset->size(); i++)
    {
        file << getPredict(dataset->at(i)) << '\n';
    }

    file.close();
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

void RandomForest::importFromFile(string filename)
{
    ifstream file("savedData.txt");
    vector<string> importData;
    string curData = "";
    while (!file.eof())
    {
        string line;
        getline(file, line);
        if (line == "-")
        {
            importData.push_back(curData);
            curData = "";
        }
        else
        {
            curData += line + ' ';
        }
    }

    forest.resize(importData.size());
    for (int i = 0; i < forest.size(); i++)
    {
        forest[i] = new Tree(false);
        forest[i]->import(importData[i]);
    }

    file.close();
}

void RandomForest::exportToFile(string filename)
{
    ofstream file(filename);

    for (int i = 0; i < forest.size(); i++)
    {
        file << forest[i]->getExport() << '\n';
        file << '-' << '\n';
    }

    file.close();
}

RandomForest *buildBestModel(DataSet *dataset, DataSet *valid, int numberOfTrees)
{
    RandomForest *bestForest = NULL;
    double acc = 0.0;
    for (int minSize = 1; minSize <= 3; minSize++)
    {
        for (int maxDepth = 3; maxDepth <= 8; maxDepth++)
        {
            RandomForest *randomForest = new RandomForest(dataset, minSize, maxDepth, 100, false);
            double curAcc = randomForest->calcAccuracy(valid);
            if (acc < curAcc)
            {
                acc = curAcc;
                bestForest = randomForest;
            }
        }
    }
    return bestForest;
}
