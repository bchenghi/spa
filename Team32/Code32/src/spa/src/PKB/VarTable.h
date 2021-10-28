#ifndef GUARD_VAR_TABLE_H
#define GUARD_VAR_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class VarTable : public Table<VarIndex, VarName> {
public:
    static VarTable* getInstance() {
        if (var_table_ptr == nullptr) {
            var_table_ptr = new VarTable;
        }
        return var_table_ptr;
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
    static VarTable* var_table_ptr;
    static const size_t INDEX_TO_NAME_MAP = 1;
    static const size_t NAME_TO_INDEX_MAP = 21;

    VarTable() {
        one_to_one_map[INDEX_TO_NAME_MAP] = std::unordered_map<VarIndex, VarName>();
        one_to_one_rev_map[NAME_TO_INDEX_MAP] = std::unordered_map<VarName, VarIndex>();
    }
};

#endif // GUARD_VAR_TABLE_H
