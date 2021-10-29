#ifndef GUARD_VAR_TABLE_H
#define GUARD_VAR_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class VarTable : public Table<VarIndex, VarName> {
public:
    static VarTable* getInstance() {
        if (varTablePtr == nullptr) {
            varTablePtr = new VarTable;
        }
        return varTablePtr;
    }
    static VarIndex addVar(VarName varName);
    static VarName getVarName(VarIndex index);
    static VarIndex getVarIndex(VarName varName);
    static ListOfVarNames getAllVarName();
    static int getSize();
    static void clear();

private:
    //static std::unordered_map<VarIndex, VarName> indexToNameMap;
    //static std::unordered_map<VarName, VarIndex> nameToIndexMap;
    static int size;
    static VarTable* varTablePtr;
    static inline const size_t INDEX_TO_NAME_MAP = 1;
    static inline const size_t NAME_TO_INDEX_MAP = 2;

    VarTable() {
        oneToOneMap[INDEX_TO_NAME_MAP] = std::unordered_map<VarIndex, VarName>();
        oneToOneRevMap[NAME_TO_INDEX_MAP] = std::unordered_map<VarName, VarIndex>();
    }
};

#endif // GUARD_VAR_TABLE_H
