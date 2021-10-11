#ifndef GUARD_CALL_STMT_TABLE_H
#define GUARD_CALL_STMT_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class CallStmtTable {
public:
    static bool insert(StmtNo, const ProcName&);
    static std::unordered_map<StmtNo, ProcName> getAll();
    static void clear();
private:
    static std::unordered_map<StmtNo, ProcName> callStmtToProcMap;
};

#endif
