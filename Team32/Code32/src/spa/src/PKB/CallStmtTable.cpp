#include "CallStmtTable.h"

CallStmtTable* CallStmtTable::callstmt_table_ptr = nullptr;

bool CallStmtTable::insert(StmtNo stmtNo, const ProcName& procName)
{
    if (!getInstance()->is_one_to_one_empty(CALL_PROC_MAP, stmtNo)) {
        return false;
    }
    return getInstance()->add_one_to_one(CALL_PROC_MAP, stmtNo, procName)
        && getInstance()->add_one_to_many_rev(PROC_CALL_MAP, procName, stmtNo);
}

ProcName CallStmtTable::getProcCalled(StmtNo stmtNo) {
    return getInstance()->get_one_to_one(CALL_PROC_MAP, stmtNo);
}

ListOfStmtNos CallStmtTable::getCallStmtsOfProcCalled(const ProcName& procName) {
    return getInstance()->get_one_to_many_rev(PROC_CALL_MAP, procName);
}

const std::unordered_map<StmtNo, ProcName> & CallStmtTable::getCallStmtToProcMap()
{
    return getInstance()->get_one_to_one_map(CALL_PROC_MAP);
}

const std::unordered_map<ProcName, ListOfStmtNos> & CallStmtTable::getProcToCallStmtsMap() {
    return getInstance()->get_one_to_many_rev_map(PROC_CALL_MAP);
}

void CallStmtTable::clear()
{
    getInstance()->clearAll();
}
