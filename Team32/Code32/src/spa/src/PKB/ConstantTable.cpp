#include "ConstantTable.h"

LIST_OF_CONSTANT constantsSet;

bool ConstantTable::addConstant(int c)
{
	if (constantsSet.count(c) == 1) {
		return true;
	}
	else {
		constantsSet.insert(c);
		return true;
	}
	return false;
}

bool ConstantTable::ifConstant(int c)
{
	if (constantsSet.count(c) == 1) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

LIST_OF_CONSTANT ConstantTable::getAllConstant()
{
	return constantsSet;
}
