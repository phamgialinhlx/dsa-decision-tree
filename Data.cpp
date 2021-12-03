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
Data::Data(char _label, vector<int> _att, int _index) : label(_label), attribute(_att), index(_index) {}

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
        Data* temp = new Data(line);
        temp->index = dataSet->size();
        dataSet->push_back(temp);
    }
    return dataSet;

}

DataSet *loadDataSetBuff(string fileName, char label, int scale)
{
    DataSet *dataSet = new DataSet();
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        Data* temp = new Data(line);
        temp->index = dataSet->size();
        if (line[0] == label)
        {
            for (int i = 1; i < scale; i++)
            {
                dataSet->push_back(temp);
            }
        }
        dataSet->push_back(temp);
    }
    return dataSet;
    
}


Data* Data::clone() {
    return new Data(this->label, this->attribute, this->index);
}

DataSet *cloneDataSet(DataSet *dataSet) {
    DataSet *newDataSet = new DataSet();
    for(int i = 0; i < dataSet->size(); i++) {
        newDataSet->push_back(dataSet->at(i)->clone());
    }
    return newDataSet;
}