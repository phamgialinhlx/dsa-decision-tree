/**
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef DATA_H
#define DATA_H

// Libraries included
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Namespace used
using namespace std;

/**
 * \brief A data struct in decision tree.
 * 
 */
struct Data
{
    // Attribute setting
    static const int ATT_SIZE = 4; // <- - - Attributes size change here!
    static const int ATT_MAX = 5;  // <- - - Attributes max value change here!
    static const int ATT_MIN = 1;  // <- - - Attributes min value change here!

    // Label setting
    static const string LABEL;

    // There are three labels: 'L', 'R', 'B'
    char label;

    // Attribute vector contains values which are the attributes of the data.
    vector<int> attribute;

    // Default constructor.
    Data();

    // Constructor with full params.
    Data(char _label, vector<int> _att);

    // Constructor with one line string.
    Data(string line);

    // Destructor.
    ~Data();

    // toString function returns a string that contains
    // label and all the values of attribute vector.
    string toString();
};

// DataSet type
typedef vector<Data *> DataSet;
// Group DataSet type
typedef pair<DataSet *, DataSet *> GroupDataSet;

// loadDataSet function return vector of Data that read from file.
DataSet *loadDataSet(string fileName);

#endif