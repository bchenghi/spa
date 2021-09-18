#include "UseTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<STMT_NO, LIST_OF_VAR_NAME> UseTable::stmtUseMap;
unordered_map<PROC_NAME, LIST_OF_VAR_NAME> UseTable::procUseMap;

bool UseTable::addStmtUse(STMT_NO stmt, VAR_NAME varName)
{
    auto res = UseTable::stmtUseMap.find(stmt);
    if (res != UseTable::stmtUseMap.end()) {
        LIST_OF_VAR_NAME *varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        UseTable::stmtUseMap[stmt] = LIST_OF_VAR_NAME();
        UseTable::stmtUseMap[stmt].insert(varName);
        return true;
    }
}

bool UseTable::addProcUse(PROC_NAME procName, VAR_NAME varName)
{
    auto res = UseTable::procUseMap.find(procName);
    if (res != UseTable::procUseMap.end()) {
        LIST_OF_VAR_NAME* varList = &(res->second);
        varList->insert(varName);
        return true;
    }
    else {
        UseTable::procUseMap[procName] = LIST_OF_VAR_NAME();
        UseTable::procUseMap[procName].insert(varName);
        return true;
    }
}

bool UseTable::isStmtUse(STMT_NO stmt, VAR_NAME varName)
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

bool UseTable::isProcUse(PROC_NAME procName, VAR_NAME varName)
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

LIST_OF_VAR_NAME UseTable::getStmtUse(STMT_NO stmt)
{
    auto res = UseTable::stmtUseMap.find(stmt);
    if (res != UseTable::stmtUseMap.end()) {
        return res->second;
    }
    else {
        return LIST_OF_VAR_NAME();
    }
}

LIST_OF_VAR_NAME UseTable::getProcUse(PROC_NAME procName)
{
    auto res = UseTable::procUseMap.find(procName);
    if (res != UseTable::procUseMap.end()) {
        return res->second;
    }
    else {
        return LIST_OF_VAR_NAME();
    }
}

const unordered_map<STMT_NO, LIST_OF_VAR_NAME> & UseTable::getStmtUseMap() {
    return stmtUseMap;
}

const unordered_map<PROC_NAME, LIST_OF_VAR_NAME> & UseTable::getProUseMap() {
    return procUseMap;
}

void UseTable::clear() {
    stmtUseMap.clear();
    procUseMap.clear();
}
