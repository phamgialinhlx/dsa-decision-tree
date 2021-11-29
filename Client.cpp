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

    vector<Data *> *dataset = loadDataSet("train.txt");
    cout << "Load done!\n";

    Tree *tree = new Tree();
    tree->buildTree(dataset, 1, 20);
    cout << "Build done!\n";

    tree->printTree();
    cout << "END" << endl;

    return 0;
}