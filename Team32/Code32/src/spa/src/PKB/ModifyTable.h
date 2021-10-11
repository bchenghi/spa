#ifndef GUARD_MODIFY_TABLE_H
#define GUARD_MODIFY_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class ModifyTable {
public:
    static bool addStmtModify(StmtNo stmt, VarName varName);
    static bool addProcModify(ProcName procName, VarName varName);
    static bool isStmtModify(StmtNo stmt, VarName varName);
    static bool isProcModify(ProcName procName, VarName varName);
    static ListOfVarNames getStmtModify(StmtNo stmt);
    static ListOfVarNames getProcModify(ProcName procName);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getStmtModifyMap();
    static std::unordered_map<ProcName, ListOfVarNames> getProcModifyMap();
    static void clear();

private:
    static std::unordered_map<StmtNo, ListOfVarNames> stmtModifyMap;
    static std::unordered_map<ProcName, ListOfVarNames> procModifyMap;
};

#endif // GUARD_MODIFY_TABLE_H
