#include "CallStmtTable.h"

std::unordered_map<StmtNo, ProcName> CallStmtTable::callStmtToProcMap;
std::unordered_map<ProcName, ListOfStmtNos> CallStmtTable::procToCallStmtsMap;

bool CallStmtTable::insert(StmtNo stmtNo, const ProcName& procName)
{
    if (callStmtToProcMap.find(stmtNo) != callStmtToProcMap.end())
        return false;

    if (procToCallStmtsMap.find(procName) == procToCallStmtsMap.end())
        procToCallStmtsMap[procName] = {};

    callStmtToProcMap[stmtNo] = procName;
    procToCallStmtsMap[procName].insert(stmtNo);

    return true;
}

ProcName CallStmtTable::getProcCalled(StmtNo stmtNo) {
    const auto procIter = callStmtToProcMap.find(stmtNo);

    return procIter == callStmtToProcMap.end() ? "" : procIter->second;
}

ListOfStmtNos CallStmtTable::getCallStmtsOfProcCalled(const ProcName& procName) {
    const auto stmtsIter = procToCallStmtsMap.find(procName);

    return stmtsIter == procToCallStmtsMap.end() ? ListOfStmtNos() : stmtsIter->second;
}

std::unordered_map<StmtNo, ProcName> CallStmtTable::getCallStmtToProcMap()
{
    return callStmtToProcMap;
}

std::unordered_map<ProcName, ListOfStmtNos> CallStmtTable::getProcToCallStmtsMap() {
    return procToCallStmtsMap;
}

void CallStmtTable::clear()
{
    callStmtToProcMap.clear();
    procToCallStmtsMap.clear();
}
