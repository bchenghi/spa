#include "UseTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<StmtNo, ListOfVarNames> UseTable::stmtUseMap;
unordered_map<ProcName, ListOfVarNames> UseTable::procUseMap;

bool UseTable::addStmtUse(StmtNo stmt, VarName varName)
{
    auto res = UseTable::stmtUseMap.find(stmt);
    if (res != UseTable::stmtUseMap.end()) {
        ListOfVarNames *varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        UseTable::stmtUseMap[stmt] = ListOfVarNames();
        UseTable::stmtUseMap[stmt].insert(varName);
        return true;
    }
}

bool UseTable::addProcUse(ProcName procName, VarName varName)
{
    auto res = UseTable::procUseMap.find(procName);
    if (res != UseTable::procUseMap.end()) {
        ListOfVarNames* varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        UseTable::procUseMap[procName] = ListOfVarNames();
        UseTable::procUseMap[procName].insert(varName);
        return true;
    }
}

bool UseTable::isStmtUse(StmtNo stmt, VarName varName)
{
    auto res = UseTable::stmtUseMap.find(stmt);
    if (res != UseTable::stmtUseMap.end()) {
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

bool UseTable::isProcUse(ProcName procName, VarName varName)
{
    auto res = UseTable::procUseMap.find(procName);
    if (res != UseTable::procUseMap.end()) {
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

ListOfVarNames UseTable::getStmtUse(StmtNo stmt)
{
    auto res = UseTable::stmtUseMap.find(stmt);
    if (res != UseTable::stmtUseMap.end()) {
        return res->second;
    }
    else {
        return ListOfVarNames();
    }
}

ListOfVarNames UseTable::getProcUse(ProcName procName)
{
    auto res = UseTable::procUseMap.find(procName);
    if (res != UseTable::procUseMap.end()) {
        return res->second;
    }
    else {
        return ListOfVarNames();
    }
}

const unordered_map<StmtNo, ListOfVarNames> & UseTable::getStmtUseMap() {
    return stmtUseMap;
}

const unordered_map<ProcName, ListOfVarNames> & UseTable::getProUseMap() {
    return procUseMap;
}

void UseTable::clear() {
    stmtUseMap.clear();
    procUseMap.clear();
}
