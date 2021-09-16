#include "ConstantTable.h"

LIST_OF_CONSTANT ConstantTable::constantsSet;

bool ConstantTable::addConstant(int c)
{
	if (ConstantTable::constantsSet.count(c) == 1) {
		return true;
	}
	else {
		ConstantTable::constantsSet.insert(c);
		return true;
	}
	return false;
}

bool ConstantTable::ifConstant(int c)
{
	if (ConstantTable::constantsSet.count(c) == 1) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

LIST_OF_CONSTANT ConstantTable::getAllConstant()
{
	return ConstantTable::constantsSet;
}

void ConstantTable::clear() {
    constantsSet.clear();
}
