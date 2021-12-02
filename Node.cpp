#include "Node.h"
#include "TerminalNode.h"
#include "DecisionNode.h"

SplitData::GroupSplitData getSplit(vector<Data *> *dataset, SplitData::SPLIT_VAL method)
{
    SplitData::GroupSplitData chosenGroup;
    for (int atr = 0; atr < Data::ATT_SIZE; atr++)
    {
        SplitData::GroupSplitData curGroup;
        switch (method)
        {
        case SplitData::ATTRIBUTE:
            curGroup = SplitData::Attribute::getSplit(dataset, atr);
            break;

        case SplitData::COMPARISON:
            curGroup = SplitData::Comparison::getSplit(dataset, atr);
            break;

        case SplitData::COMBINATION:
            curGroup = SplitData::Combination::getSplit(dataset, atr);
            break;

        default:
            curGroup = SplitData::GroupSplitData();
            break;
        }

        if (curGroup.giniIndex < chosenGroup.giniIndex)
        {
            chosenGroup = curGroup;
        }
    }
    return chosenGroup;
}

vector<int> getRandomAtt()
{
    int randomSize = rand() % 2 + 2;
    vector<int> result(randomSize);
    vector<int> value(Data::ATT_SIZE);
    for (int i = 0; i < Data::ATT_SIZE; i++)
    {
        value[i] = i;
    }
    for (int i = 0; i < randomSize; i++)
    {
        int temp = rand() % (Data::ATT_SIZE - i) + i;
        swap(value[i], value[temp]);
        result[i] = value[i];
    }
    return result;
}

SplitData::GroupSplitData getRandomSplit(vector<Data *> *dataset, SplitData::SPLIT_VAL method)
{
    SplitData::GroupSplitData chosenGroup;
    vector<int> randomAtt = getRandomAtt();
    for (int i = 0; i < randomAtt.size(); i++)
    {
        SplitData::GroupSplitData curGroup;
        switch (method)
        {
        case SplitData::ATTRIBUTE:
            curGroup = SplitData::Attribute::getSplit(dataset, randomAtt[i]);
            break;

        case SplitData::COMPARISON:
            curGroup = SplitData::Comparison::getSplit(dataset, randomAtt[i]);
            break;

        case SplitData::COMBINATION:
            curGroup = SplitData::Combination::getSplit(dataset, randomAtt[i]);
            break;

        default:
            curGroup = SplitData::GroupSplitData();
            break;
        }

        if (curGroup.giniIndex < chosenGroup.giniIndex)
        {
            chosenGroup = curGroup;
        }
    }
    return chosenGroup;
}

char toTerminal(DataSet *data)
{
    vector<int> cnt(Data::LABEL.size(), 0);

    for (int index = 0; index < data->size(); index++)
        for (int label = 0; label < Data::LABEL.size(); label++)
            if (data->at(index)->label == Data::LABEL[label])
            {
                ++cnt[label];
                break;
            }

    int cur = 0;
    for (int label = 0; label < Data::LABEL.size(); label++)
        if (cnt[label] > cnt[cur])
            cur = label;

    return Data::LABEL[cur];
}

// Create child splits for a node or make terminal
void split(Node *&node, DataSet *dataset, int minSize, int maxDepth, int depth)
{
    SplitData::GroupSplitData tempGroup = getRandomSplit(dataset, SplitData::COMPARISON);

    if (tempGroup.group == NULL)
    {
        node = new TerminalNode(toTerminal(dataset));
        return;
    }

    DataSet *left = tempGroup.group->first;
    DataSet *right = tempGroup.group->second;

    if ((tempGroup.giniIndex == 0.0) || (depth >= maxDepth) || (left->size() <= minSize && right->size() <= minSize))
    {
        char leftLabel = toTerminal(left);
        char rightLabel = toTerminal(right);
        if (leftLabel == rightLabel)
        {
            node = new TerminalNode(leftLabel);
        }
        else
        {
            node = new DecisionNode(tempGroup.attribute, tempGroup.compareValue, tempGroup.method);
            node->left = new TerminalNode(leftLabel);
            node->right = new TerminalNode(rightLabel);
        }
        return;
    }

    node = new DecisionNode(tempGroup.attribute, tempGroup.compareValue, tempGroup.method);

    if (left->size() <= minSize)
        node->left = new TerminalNode(toTerminal(left));
    else
        split(node->left, left, minSize, maxDepth, depth + 1);

    if (right->size() <= minSize)
        node->right = new TerminalNode(toTerminal(right));
    else
        split(node->right, right, minSize, maxDepth, depth + 1);

    return;
}