/*
 * This file is part of dsa-decision-tree
 *
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh.
 */

#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Console
{
private:
    string name;
    bool enable;

public:
    Console(string _name = "", bool _enable = true);

    ~Console();

    bool isEnable();

    void setEnable(bool _enable);

    template <typename... Args>
    constexpr void log(ostream &os, Args &&...args) noexcept
    {
        if (enable)
        {
            os << "[" << name << "] ";
            ((os << forward<Args>(args)), ...);
            os << "\n";
        }
    }
};

#endif