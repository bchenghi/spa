#include "VarTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<VarIndex, VarName> VarTable::indexToNameMap;
unordered_map<VarName, VarIndex> VarTable::nameToIndexMap;
int VarTable::size = 0;

VarIndex VarTable::addVar(VarName varName)
{
    auto res = VarTable::nameToIndexMap.find(varName);
    VarIndex varIndex = 0;
    if (res != VarTable::nameToIndexMap.end()) {
        varIndex = res->second;
    }
    else {
        varIndex = (VarIndex) ++VarTable::size;
        VarTable::nameToIndexMap[varName] = varIndex;
        VarTable::indexToNameMap[varIndex] = varName;
    }
    return varIndex;
}

VarName VarTable::getVarName(VarIndex index)
{
    auto res = VarTable::indexToNameMap.find(index);
    if (res != VarTable::indexToNameMap.end()) {
        return res->second;
    }
    else {
        throw "Unable to find (VarTable)";
    }
}

VarIndex VarTable::getVarIndex(VarName varName)
{
    auto res = VarTable::nameToIndexMap.find(varName);
    if (res != VarTable::nameToIndexMap.end()) {
        return res->second;
    }
    else {
        throw "Unable to find (VarTable)";
    }
}

ListOfVarNames VarTable::getAllVarName()
{
    ListOfVarNames varNameList;
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
