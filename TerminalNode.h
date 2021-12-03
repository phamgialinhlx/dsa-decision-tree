/*
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#pragma once
#ifndef TERMINAL_NODE_H
#define TERMINAL_NODE_H

#include "Data.h"
#include "Node.h"
#include "Node.h"

class TerminalNode : virtual public Node
{
    private:
        char label;

    public:
        TerminalNode(char lab);
        ~TerminalNode();

        bool isTerminal();

        bool compare(Data *data);

        char getLabel();

        string toString();

        void setCode(int _code);

        string getExport();
};

#endif