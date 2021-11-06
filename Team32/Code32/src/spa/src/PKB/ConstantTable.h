#ifndef GUARD_CONSTANT_TABLE_H
#define GUARD_CONSTANT_TABLE_H

#include "TypePreDefine.h"

class ConstantTable {
public:
    static bool addConstant(int c);
    static bool ifConstant(int c);
    static ListOfConstants getAllConstant();
    static void clear();
private:
    static ListOfConstants constantsSet;
};

#endif
