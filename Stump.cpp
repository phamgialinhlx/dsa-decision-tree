/**
 * This file is part of dsa-decision-tree
 * 
 * Developed for the DSA UET course.
 * This project was developed by Ba Luong and Gia Linh. 
 */

#include "Stump.h"

Stump::Stump(int atr, int value, SplitData::SPLIT_VAL met, double _significance) : attribute(atr), compareValue(value), method(met), significance(_significance) { this->left = this->right = NULL; }

bool Stump::compare(Data *data)
{
    switch (method)
    {
    case SplitData::ATTRIBUTE:
        return SplitData::Attribute::compare(data, attribute, compareValue);

    case SplitData::COMPARISON:
        return SplitData::Comparison::compare(data, attribute, compareValue);

    case SplitData::COMBINATION:
        return SplitData::Combination::compare(data, attribute, compareValue);

    default:
        cout << "[EXCEPTION] Unknown method" << endl;
        return true;
    }
}

bool Stump::isTerminal()
{
    return false;
}

char Stump::getLabel()
{
    return ' ';
}

string Stump::toString()
{
    stringstream ss;
    ss << "Stump: " << attribute << " " << compareValue << " "
       << method << " " << significance << " " << left->getLabel()
       << " " << right->getLabel();
    return ss.str();
}

char Stump::predict(vector<int> attribute)
{
    switch (method)
    {
    case SplitData::ATTRIBUTE:
        if (attribute.at(this->attribute) == compareValue)
            return this->left->getLabel();
        else
            return this->right->getLabel();
        ;
        break;

    case SplitData::COMPARISON:
        if (attribute.at(this->attribute) < compareValue)
        {
            return this->left->getLabel();
        }
        else
        {
            return this->right->getLabel();
        }
        break;

    case SplitData::COMBINATION:
        if (getBit(compareValue, attribute.at(this->attribute) - 1))
            return this->left->getLabel();
        else
            return this->right->getLabel();
    default:
        cout << "default" << endl;
        break;
    }
}

double Stump::getSignificance()
{
    return significance;
}


void Stump::setCode(int _code)
{
    code = _code;
}

string Stump::getExport() {
    return "";
}