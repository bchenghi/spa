#include "CallStmtTable.h"

std::unordered_map<StmtNo, ProcName> CallStmtTable::callStmtToProcMap;

bool CallStmtTable::insert(StmtNo stmtNo, const ProcName& procName)
{
    if (callStmtToProcMap.find(stmtNo) != callStmtToProcMap.end())
        return false;

    callStmtToProcMap[stmtNo] = procName;

    return true;
}

std::unordered_map<StmtNo, ProcName> CallStmtTable::getAll()
{
    return callStmtToProcMap;
}

void CallStmtTable::clear()
{
    callStmtToProcMap.clear();
}
