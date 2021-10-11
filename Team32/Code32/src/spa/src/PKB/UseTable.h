#ifndef GUARD_USE_TABLE_H
#define GUARD_USE_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class UseTable {
public:
    static bool addStmtUse(StmtNo stmt, VarName varName);
    static bool addProcUse(ProcName procName, VarName varName);
    static bool isStmtUse(StmtNo stmt, VarName varName);
    static bool isProcUse(ProcName procName, VarName varName);
    static ListOfVarNames getStmtUse(StmtNo stmt);
    static ListOfVarNames getProcUse(ProcName procName);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getStmtUseMap();
    static const std::unordered_map<ProcName, ListOfVarNames>& getProcUseMap();
    static void clear();

private:
    static std::unordered_map<StmtNo, ListOfVarNames> stmtUseMap;
    static std::unordered_map<ProcName, ListOfVarNames> procUseMap;
};

#endif // GUARD_USE_TABLE_H
