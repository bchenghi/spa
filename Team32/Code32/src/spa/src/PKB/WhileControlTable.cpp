#include "WhileControlTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<StmtNo, ListOfVarNames> WhileControlTable::whileToVarListMap;
unordered_map<VarName, ListOfStmtNos> WhileControlTable::varToWhileListMap;

bool WhileControlTable::addWhileControlVars(StmtNo while_stmt, VarName var)
{
    auto res1 = WhileControlTable::whileToVarListMap.find(while_stmt);
    auto res2 = WhileControlTable::varToWhileListMap.find(var);
    if (res1 != WhileControlTable::whileToVarListMap.end()) {
        WhileControlTable::whileToVarListMap[while_stmt].insert(var);
        if (res2 != WhileControlTable::varToWhileListMap.end()) {
            WhileControlTable::varToWhileListMap[var].insert(while_stmt);
        }
        else {
            WhileControlTable::varToWhileListMap[var] = ListOfStmtNos();
            WhileControlTable::varToWhileListMap[var].insert(while_stmt);
        }
        return true;
    }
    else {
        WhileControlTable::whileToVarListMap[while_stmt] = ListOfVarNames();
        WhileControlTable::whileToVarListMap[while_stmt].insert(var);
        if (res2 != WhileControlTable::varToWhileListMap.end()) {
            WhileControlTable::varToWhileListMap[var].insert(while_stmt);
        }
        else {
            WhileControlTable::varToWhileListMap[var] = ListOfStmtNos();
            WhileControlTable::varToWhileListMap[var].insert(while_stmt);
        }
        return true;
    }
}

bool WhileControlTable::isWhileControlVars(StmtNo while_stmt, VarName var)
{
    auto res = WhileControlTable::whileToVarListMap.find(while_stmt);
    if (res != WhileControlTable::whileToVarListMap.end()) {
        if (res->second.count(var) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

ListOfVarNames WhileControlTable::getWhileControlVars(StmtNo while_stmt)
{
    auto res = WhileControlTable::whileToVarListMap.find(while_stmt);
    if (res != WhileControlTable::whileToVarListMap.end()) {
        return res->second;
    }
    return ListOfVarNames();
}

ListOfStmtNos WhileControlTable::getWhileControlledByVar(VarName var)
{
    auto res = WhileControlTable::varToWhileListMap.find(var);
    if (res != WhileControlTable::varToWhileListMap.end()) {
        return res->second;
    }
    return ListOfStmtNos();
}

const unordered_map<StmtNo, ListOfVarNames>& WhileControlTable::getWhileToVarListMap()
{
    return whileToVarListMap;
}

const unordered_map<VarName, ListOfStmtNos>& WhileControlTable::getVarToWhileListMap()
{
    return varToWhileListMap;
}

void WhileControlTable::clear() {
    whileToVarListMap.clear();
    varToWhileListMap.clear();
}