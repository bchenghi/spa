#include "CallStmtTable.h"

CallStmtTable* CallStmtTable::callStmtTablePtr = nullptr;

bool CallStmtTable::insert(StmtNo stmtNo, const ProcName& procName)
{
    if (!getInstance()->isOneToOneEmpty(CALL_PROC_MAP, stmtNo)) {
        return false;
    }
    return getInstance()->addOneToOne(CALL_PROC_MAP, stmtNo, procName)
        && getInstance()->addOneToManyRev(PROC_CALL_MAP, procName, stmtNo);
}

ProcName CallStmtTable::getProcCalled(StmtNo stmtNo) {
    return getInstance()->getOneToOne(CALL_PROC_MAP, stmtNo);
}

ListOfStmtNos CallStmtTable::getCallStmtsOfProcCalled(const ProcName& procName) {
    return getInstance()->getOneToManyRev(PROC_CALL_MAP, procName);
}

const std::unordered_map<StmtNo, ProcName> & CallStmtTable::getCallStmtToProcMap()
{
    return getInstance()->getOneToOneMap(CALL_PROC_MAP);
}

const std::unordered_map<ProcName, ListOfStmtNos> & CallStmtTable::getProcToCallStmtsMap() {
    return getInstance()->getOneToManyRevMap(PROC_CALL_MAP);
}

void CallStmtTable::clear()
{
    getInstance()->clearAll();
}
