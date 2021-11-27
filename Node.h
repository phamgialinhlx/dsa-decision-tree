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
#include <math.h>
using namespace std;

//Split a dataset based on an attribute and attribute value
vector<Data *> * splitByAttribute(vector<Data *> *data, int atr, int value);

struct Node
{
    double giniScore;
    int attribute;
    
    Node *left;
    Node *right;
};

// Compute the Gini index for a plit dataset
double getGiniScore(vector<Data *> *data, int atr[])
{
    return 0;
}

// Compute the Entropy index for a plit dataset
// TODO: COMPLETE getEntropyScore() method.
double getEntropyScore(vector<Data *> *data, int atr, vector<int> combination) {
    int numberOfData = data->size();
    cout << "Numbers of datas = " << numberOfData << endl;
    int count[Data::NUMBER_LABELS][2];
    double result = 0;
    for (int i = 0; i < Data::NUMBER_LABELS; i++) {
        for(int j = 0; j < 2; j++) {
            count[i][j] = 0;
        }
    }

    for (int i = 0; i < numberOfData; i++) {
        int value = data->at(i)->att.at(atr);
        cout << value << " ";
        bool check = false;
        for (int j = 0; j < combination.size(); j++) {
            if (value == combination[j]){
                check = true;
                break;
            }
        }
        cout << boolalpha << check << endl;
        char label = data->at(i)->label;
        int pos = 1;
        if (check)
        {
            pos = 0;
        }
        if (label == 'L')
        {
            count[0][pos]++;
        } else if (label == 'R') {
            count[1][pos]++;
        } else {
            count[2][pos]++;
        }
    }
    
    int numbers1 = 0;
    int numbers2 = 0;
    for (int i = 0; i < Data::NUMBER_LABELS; i++) {
        numbers1 += count[i][0];
        numbers2 += count[i][1];
    }

    cout << "numbers1 = " << numbers1 << endl;
    cout << "numbers2 = " << numbers2 << endl;

    
    double entropy1 = 0;
    double entropy2 = 0;


    for (int i = 0; i < Data::NUMBER_LABELS; i++) {
        double temp = count[i][0] * 1.0 / numbers1;
        if (temp != 0) entropy1 -= temp*log(temp);
        temp = count[i][1] * 1.0 / numbers2;
        if (temp != 0) entropy2 -= temp*log(temp);
        
    }

    cout << "Entropy 1 = " <<  entropy1 << endl;
    cout << "Entropy 2 = " <<  entropy2 << endl;


    result = numbers1 * entropy1 / (numbers1 + numbers2) +
             numbers2 * entropy2 / (numbers1 + numbers2);


    return result;
}


//Split a dataset based on an attribute and attribute value
vector<Data *> * splitByAttribute(vector<Data *> *data, int atr, int value)
{   
    vector<Data *> *group = new vector<Data*>();
    for (int i = 0; i < data->size(); i++) {
        if (data->at(i)->att.at(atr) == value)
            group->push_back(data->at(i));
    }
    return group;    
}


// Select the best split point for a dataset
pair<vector<Data *>, vector<Data *>> getSplit(vector<Data *> *dataset)
{
    
}

#endif