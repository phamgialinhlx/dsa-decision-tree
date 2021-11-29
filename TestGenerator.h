/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef TEST_GENERATOR_H
#define TEST_GENERATOR_H

// Libraries included
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>

// Headers included
#include "Data.h"

// Namespace used
using namespace std;

/**
 * \brief DataGenerator is a namespace that contains functions help us generate 
 * new Data!
 */
namespace DataGenerator
{
    // Random setting
    // Set the seed to the current time!
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // attGen function returns an integer number which is the value of one attribute.
    int attGen();

    // labelGen function return the label of an attribute vector.
    char labelGen(vector<int> att);

    // dataGen function return a random Data.
    Data dataGen();

    // testGen function returns a vector of Data.
    //  numberOfData is the number of random data.
    vector<Data> testGen(int numberOfData = 100);
}

class TestGenerator
{
private:
    // Output file setting
    string outputFile = "testNew.txt"; // default file name!

    // Just print the test to the output file (or console).
    void print(vector<Data> test);

public:
    TestGenerator() {}
    ~TestGenerator() {}
    TestGenerator(string _outputFile);

    void setFileName(string _outputFile);
    void generate(int numberOfData = 100);
};

#endif