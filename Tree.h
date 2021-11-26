/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Data.h"

struct Tree {
    Node* root;

    Tree(string filepath) {
        vector<Data *> *dataset = loadDataSet("train.txt");

    }

    void buildTree(vector<Data *> *dataset, int minSize, int maxDepth)
    {
        return;
    }
};

#endif
