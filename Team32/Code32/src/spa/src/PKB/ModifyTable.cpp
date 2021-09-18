#include "ModifyTable.h"

#include <unordered_map>

std::unordered_map<StmtNo, ListOfVarNames> ModifyTable::stmtModifyMap;
std::unordered_map<ProcName, ListOfVarNames> ModifyTable::procModifyMap;

bool ModifyTable::addStmtModify(StmtNo stmt, VarName varName)
{
    auto res = ModifyTable::stmtModifyMap.find(stmt);
    if (res != ModifyTable::stmtModifyMap.end()) {
        ListOfVarNames* varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        ModifyTable::stmtModifyMap[stmt] = ListOfVarNames();
        ModifyTable::stmtModifyMap[stmt].insert(varName);
        return true;
    }
}

bool ModifyTable::addProcModify(ProcName procName, VarName varName)
{
    auto res = ModifyTable::procModifyMap.find(procName);
    if (res != ModifyTable::procModifyMap.end()) {
        ListOfVarNames* varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        ModifyTable::procModifyMap[procName] = ListOfVarNames();
        ModifyTable::procModifyMap[procName].insert(varName);
        return true;
    }
}

bool ModifyTable::isStmtModify(StmtNo stmt, VarName varName)
{
    auto res = ModifyTable::stmtModifyMap.find(stmt);
    if (res != ModifyTable::stmtModifyMap.end()) {
        if (res->second.count(varName) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool ModifyTable::isProcModify(ProcName procName, VarName varName)
{
    auto res = ModifyTable::procModifyMap.find(procName);
    if (res != ModifyTable::procModifyMap.end()) {
        if (res->second.count(varName) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

ListOfVarNames ModifyTable::getStmtModify(StmtNo stmt)
{
    auto res = ModifyTable::stmtModifyMap.find(stmt);
    if (res != ModifyTable::stmtModifyMap.end()) {
        return res->second;
    }
    else {
        return ListOfVarNames();
    }
}

ListOfVarNames ModifyTable::getProcModify(ProcName procName)
{
    auto res = ModifyTable::procModifyMap.find(procName);
    if (res != ModifyTable::procModifyMap.end()) {
        return res->second;
    }
    else {
        return ListOfVarNames();
    }
}

const std::unordered_map<StmtNo, ListOfVarNames>& ModifyTable::getStmtModifyMap()
{
    return stmtModifyMap;
}

std::unordered_map<ProcName, ListOfVarNames> ModifyTable::getProcModifyMap()
{
    return procModifyMap;
}

void ModifyTable::clear()
{
    stmtModifyMap.clear();
    procModifyMap.clear();
}
