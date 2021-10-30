#include "VarTable.h"

VarTable* VarTable::varTablePtr = nullptr;
int VarTable::size = 0;

VarIndex VarTable::addVar(VarName varName)
{
    if (!getInstance()->isOneToOneRevEmpty(NAME_TO_INDEX_MAP, varName)) {
        return getInstance()->getOneToOneRev(NAME_TO_INDEX_MAP, varName);
    }
    size++;
    getInstance()->addOneToOne(INDEX_TO_NAME_MAP, size, varName);
    getInstance()->addOneToOneRev(NAME_TO_INDEX_MAP, varName, size);
    return size;
}

VarName VarTable::getVarName(VarIndex index)
{
    if (getInstance()->isOneToOneEmpty(INDEX_TO_NAME_MAP, index)) {
        throw "Unable to find (VarTable)";
    }
    return getInstance()->getOneToOne(INDEX_TO_NAME_MAP, index);
}

VarIndex VarTable::getVarIndex(VarName varName)
{
    if (getInstance()->isOneToOneRevEmpty(NAME_TO_INDEX_MAP, varName)) {
        throw "Unable to find (VarTable)";
    }
    return getInstance()->getOneToOneRev(NAME_TO_INDEX_MAP, varName);
}

ListOfVarNames VarTable::getAllVarName()
{
    std::unordered_map<VarName, VarIndex> tmp_ = getInstance()->getOneToOneRevMap(NAME_TO_INDEX_MAP);
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
