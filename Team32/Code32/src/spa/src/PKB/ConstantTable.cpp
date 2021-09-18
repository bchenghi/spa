#include "ConstantTable.h"

ListOfConstants ConstantTable::constantsSet;

bool ConstantTable::addConstant(int c)
{
    if (ConstantTable::constantsSet.count(c) == 1) {
        return true;
    }
    else {
        ConstantTable::constantsSet.insert(c);
        return true;
    }
}

bool ConstantTable::ifConstant(int c)
{
    if (ConstantTable::constantsSet.count(c) == 1) {
        return true;
    }
    else {
        return false;
    }
}

ListOfConstants ConstantTable::getAllConstant()
{
    return ConstantTable::constantsSet;
}

void ConstantTable::clear() {
    constantsSet.clear();
}
