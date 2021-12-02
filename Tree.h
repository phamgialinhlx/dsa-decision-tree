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
#include "Console.h"

class Tree
{
private:
    Node *root;
    Console *console;

public:
    Tree();

    Tree(vector<Data *> *dataset, int minSize, int maxDepth);

    ~Tree();

    /**
     * @brief Building a tree function.
     *
     * @param dataset The main dataset.
     * @param minSize Minimum Node Records.
     * @param maxDepth Maximum Tree Depth.
     */
    void buildTree(vector<Data *> *dataset, int minSize, int maxDepth);

    double calcAccuracy(DataSet *dataset);

    bool predict(Data *data);

    bool predict(Node *node, Data *data);

    char predictNode(Data *data);

    char predictNode(Node *node, Data *data);

    void printTree();
};

void printNode(Node *node, int depth);

#endif
