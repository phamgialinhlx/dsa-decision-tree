#include "Data.h"

// There are three labels: 'L', 'R', 'B'
const string Data::LABEL = "LRB";

// Default constructor.
Data::Data()
{
    //label = '';
    attribute.clear();
}

// Constructor with full params.
Data::Data(char _label, vector<int> _att) : label(_label), attribute(_att) {}

// Constructor with one line string.
Data::Data(string line)
{
    stringstream ss(line);
    ss >> label;
    int num;
    attribute.clear();
    char temp;
    while (ss >> temp)
    {
        ss >> num;
        attribute.push_back(num);
    }
}

// Destructor.
Data::~Data()
{
    attribute.clear();
}

void Data::getAttFromString(string line)
{
    stringstream ss(line);
    int num;
    attribute.clear();
    char temp;
    while (ss >> num)
    {
        ss >> temp;
        attribute.push_back(num);
    }
}

// toString function returns a string that contains
// label and all the values of attribute vector.
string Data::toString()
{
    stringstream ss;
    ss << label;
    for (int num : attribute)
    {
        ss << ',' << num;
    }
    string str;
    getline(ss, str);
    return str;
}

// loadDataSet function return vector of Data that read from file.
DataSet *loadDataSet(string fileName)
{
    DataSet *dataSet = new DataSet();
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        dataSet->push_back(new Data(line));
    }
    return dataSet;
}

DataSet *loadDataTest(string filename)
{
    DataSet *dataset = new DataSet();
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        dataset->push_back(new Data());
        dataset->back()->getAttFromString(line);
    }
    return dataset;
}


Data* Data::clone() {
    return new Data(this->label, this->attribute);
}