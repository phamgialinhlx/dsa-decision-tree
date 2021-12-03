#include "DecisionNode.h"

DecisionNode::DecisionNode() { this->left = this->right = NULL; }
DecisionNode::~DecisionNode()
{
    delete this->left;
    delete this->right;
}

DecisionNode::DecisionNode(int atr, int value, SplitData::SPLIT_VAL met) : attribute(atr), compareValue(value), method(met) { this->left = this->right = NULL; }

bool DecisionNode::isTerminal()
{
    return false;
}

bool DecisionNode::compare(Data *data)
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
        return true;
    }
}

char DecisionNode::getLabel()
{
    return ' ';
}

string DecisionNode::toString()
{
    string result;
    stringstream ss;
    ss << "[ Att[" << attribute << "] ";

    // Compare
    switch (method)
    {
    case SplitData::ATTRIBUTE:
        ss << "= " << compareValue;
        break;

    case SplitData::COMPARISON:
        ss << "< " << compareValue;
        break;

    case SplitData::COMBINATION:
        ss << "in mask: " << compareValue;
        break;

    default:
        ss << "none";
        break;            
    }
    ss << " ]";

    getline(ss, result);
    return result;
}

void DecisionNode::setCode(int _code)
{
    code = _code;
}

string DecisionNode::getExport()
{
    string result;
    stringstream ss;
    ss << isTerminal() << ' ' << attribute << ' ' << compareValue << ' ' << method;
    getline(ss, result);
    return result;
}