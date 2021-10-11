#ifndef GUARD_CALL_STMT_TABLE_H
#define GUARD_CALL_STMT_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class CallStmtTable {
public:
    static bool insert(StmtNo, const ProcName&);
    static ProcName getProcCalled(StmtNo);
    static ListOfStmtNos getCallStmtsOfProcCalled(const ProcName&);
    static std::unordered_map<StmtNo, ProcName> getCallStmtToProcMap();
    static std::unordered_map<ProcName, ListOfStmtNos> getProcToCallStmtsMap();
    static void clear();
private:
    static std::unordered_map<StmtNo, ProcName> callStmtToProcMap;
    static std::unordered_map<ProcName, ListOfStmtNos> procToCallStmtsMap;
};

#endif
