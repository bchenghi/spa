#ifndef GUARD_CONSTANT_TABLE_H
#define GUARD_CONSTANT_TABLE_H

#include "TypePreDefine.h"

class ConstantTable {
public:
	static bool addConstant(int c);
	static bool ifConstant(int c);
	static LIST_OF_CONSTANT getAllConstant();

private:
	static LIST_OF_CONSTANT constantsSet;
};

#endif // GUARD_CONSTANT_TABLE_H
