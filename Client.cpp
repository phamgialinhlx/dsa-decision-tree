/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "Tree.h"
#include "TestGenerator.h"

int main()
{
    TestGenerator testGen;
    testGen.generate();

    Tree tree("train.txt");
    cout << "END" << endl;

    return 0;
}