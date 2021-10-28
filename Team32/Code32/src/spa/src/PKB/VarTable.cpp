#include "VarTable.h"

VarTable* VarTable::var_table_ptr = nullptr;
int VarTable::size = 0;

VarIndex VarTable::addVar(VarName varName)
{
    if (!getInstance()->is_one_to_one_rev_empty(NAME_TO_INDEX_MAP, varName)) {
        return getInstance()->get_one_to_one_rev(NAME_TO_INDEX_MAP, varName);
    }
    size++;
    getInstance()->add_one_to_one(INDEX_TO_NAME_MAP, size, varName);
    getInstance()->add_one_to_one_rev(NAME_TO_INDEX_MAP, varName, size);
    return size;
}

VarName VarTable::getVarName(VarIndex index)
{
    if (getInstance()->is_one_to_one_empty(INDEX_TO_NAME_MAP, index)) {
        throw "Unable to find (VarTable)";
    }
    return getInstance()->get_one_to_one(INDEX_TO_NAME_MAP, index);
}

VarIndex VarTable::getVarIndex(VarName varName)
{
    if (getInstance()->is_one_to_one_rev_empty(NAME_TO_INDEX_MAP, varName)) {
        throw "Unable to find (VarTable)";
    }
    return getInstance()->get_one_to_one_rev(NAME_TO_INDEX_MAP, varName);
}

ListOfVarNames VarTable::getAllVarName()
{
    std::unordered_map<VarName, VarIndex> tmp_ = getInstance()->get_one_to_one_rev_map(NAME_TO_INDEX_MAP);
    ListOfVarNames varNameList;
    for (auto iter = tmp_.begin(); iter != tmp_.end(); ++iter) {
        varNameList.insert(iter->first);
    }
    return varNameList;
}

int VarTable::getSize()
{
    return VarTable::size;
}

void VarTable::clear() {
    getInstance()->clearAll();
    size = 0;
}
