#ifndef GUARD_VAR_TABLE_H
#define GUARD_VAR_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class VarTable {
public:
    static VarIndex addVar(VarName varName);
    static VarName getVarName(VarIndex index);
    static VarIndex getVarIndex(VarName varName);
    static ListOfVarNames getAllVarName();
    static int getSize();
    static void clear();

private:
    static std::unordered_map<VarIndex, VarName> indexToNameMap;
    static std::unordered_map<VarName, VarIndex> nameToIndexMap;
    static int size;
};

#endif // GUARD_VAR_TABLE_H
