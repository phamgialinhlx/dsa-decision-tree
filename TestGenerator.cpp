#include "TestGenerator.h"

// attGen function returns an integer number which is the value of one attribute.
int DataGenerator::attGen()
{
    return rng() % Data::ATT_MAX + Data::ATT_MIN;
}

// labelGen function return the label of an attribute vector.
char DataGenerator::labelGen(vector<int> att)
{
    int left = 0, right = 0;
    for (int index = 0; index < att.size(); index++)
    {
        if (index < att.size() / 2)
            left += att[index];
        else
            right += att[index];
    }
    if (left < right)
        return 'R';
    if (left > right)
        return 'L';
    return 'B';
}

// dataGen function return a random Data.
Data DataGenerator::dataGen()
{
    vector<int> att;
    att.resize(Data::ATT_SIZE, 0);
    for (int index = 0; index < att.size(); index++)
        att[index] = attGen();
    char label = labelGen(att);
    return Data(label, att);
}

// testGen function returns a vector of Data.
//  numberOfData is the number of random data.
vector<Data> DataGenerator::testGen(int numberOfData)
{
    vector<Data> test;
    test.resize(numberOfData);
    for (int index = 0; index < numberOfData; index++)
    {
        test[index] = dataGen();
    }
    return test;
}

void TestGenerator::print(vector<Data> test)
{
    ofstream file(outputFile);
    for (Data data : test)
    {
        //cout << data.toString() << '\n';
        file << data.toString() << '\n';
    }
}

TestGenerator::TestGenerator(string _outputFile) : outputFile(_outputFile) {}

void TestGenerator::setFileName(string _outputFile)
{
    outputFile = _outputFile;
}

void TestGenerator::generate(int numberOfData)
{
    cout << "Generating the test . . .";
    // Generate the test
    print(DataGenerator::testGen(numberOfData));
    cout << "Done!";
}