#include "VarTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<VAR_INDEX, VAR_NAME> VarTable::indexToNameMap;
unordered_map<VAR_NAME, VAR_INDEX> VarTable::nameToIndexMap;
int VarTable::size = 0;

VAR_INDEX VarTable::addVar(VAR_NAME varName)
{
    auto res = VarTable::nameToIndexMap.find(varName);
    VAR_INDEX varIndex = 0;
    if (res != VarTable::nameToIndexMap.end()) {
        varIndex = res->second;
    }
    else {
        varIndex = (VAR_INDEX) ++VarTable::size;
        VarTable::nameToIndexMap[varName] = varIndex;
        VarTable::indexToNameMap[varIndex] = varName;
    }
    return varIndex;
}

VAR_NAME VarTable::getVarName(VAR_INDEX index)
{
    auto res = VarTable::indexToNameMap.find(index);
    if (res != VarTable::indexToNameMap.end()) {
        return res->second;
    }
    else {
        throw "Unable to find (VarTable)";
    }
}

VAR_INDEX VarTable::getVarIndex(VAR_NAME varName)
{
    auto res = VarTable::nameToIndexMap.find(varName);
    if (res != VarTable::nameToIndexMap.end()) {
        return res->second;
    }
    else {
        throw "Unable to find (VarTable)";
    }
}

LIST_OF_VAR_NAME VarTable::getAllVarName()
{
    LIST_OF_VAR_NAME varNameList;
    for (auto iter = VarTable::nameToIndexMap.begin(); iter != VarTable::nameToIndexMap.end(); ++iter) {
        varNameList.insert(iter->first);
    }
    return varNameList;
}

int VarTable::getSize()
{
    return VarTable::size;
}

void VarTable::clear() {
    indexToNameMap.clear();
    nameToIndexMap.clear();
    size = 0;
}
