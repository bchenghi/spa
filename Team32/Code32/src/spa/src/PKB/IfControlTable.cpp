#include "IfControlTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<StmtNo, ListOfVarNames> IfControlTable::ifToVarListMap;
unordered_map<VarName, ListOfStmtNos> IfControlTable::varToIfListMap;

bool IfControlTable::addIfControlVars(StmtNo if_stmt, VarName var)
{
    auto res1 = IfControlTable::ifToVarListMap.find(if_stmt);
    auto res2 = IfControlTable::varToIfListMap.find(var);
    if (res1 != IfControlTable::ifToVarListMap.end()) {
        IfControlTable::ifToVarListMap[if_stmt].insert(var);
        if (res2 != IfControlTable::varToIfListMap.end()) {
            IfControlTable::varToIfListMap[var].insert(if_stmt);
        }
        else {
            IfControlTable::varToIfListMap[var] = ListOfStmtNos();
            IfControlTable::varToIfListMap[var].insert(if_stmt);
        }
        return true;
    }
    else {
        IfControlTable::ifToVarListMap[if_stmt] = ListOfVarNames();
        IfControlTable::ifToVarListMap[if_stmt].insert(var);
        if (res2 != IfControlTable::varToIfListMap.end()) {
            IfControlTable::varToIfListMap[var].insert(if_stmt);
        }
        else {
            IfControlTable::varToIfListMap[var] = ListOfStmtNos();
            IfControlTable::varToIfListMap[var].insert(if_stmt);
        }
        return true;
    }
}

bool IfControlTable::isIfControlVars(StmtNo if_stmt, VarName var)
{
    auto res = IfControlTable::ifToVarListMap.find(if_stmt);
    if (res != IfControlTable::ifToVarListMap.end()) {
        if (res->second.count(var) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

ListOfVarNames IfControlTable::getIfControlVars(StmtNo if_stmt)
{
    auto res = IfControlTable::ifToVarListMap.find(if_stmt);
    if (res != IfControlTable::ifToVarListMap.end()) {
        return res->second;
    }
    return ListOfVarNames();
}

ListOfStmtNos IfControlTable::getIfControlledByVar(VarName var)
{
    auto res = IfControlTable::varToIfListMap.find(var);
    if (res != IfControlTable::varToIfListMap.end()) {
        return res->second;
    }
    return ListOfStmtNos();
}

const unordered_map<StmtNo, ListOfVarNames>& IfControlTable::getIfToVarListMap()
{
    return ifToVarListMap;
}

const unordered_map<VarName, ListOfStmtNos>& IfControlTable::getVarToIfListMap()
{
    return varToIfListMap;
}

void IfControlTable::clear() {
    ifToVarListMap.clear();
    varToIfListMap.clear();
}