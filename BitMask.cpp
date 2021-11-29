#include "BitMask.h"

bool getBit(int mask, int index)
{
    return ((mask >> index) & 1);
}