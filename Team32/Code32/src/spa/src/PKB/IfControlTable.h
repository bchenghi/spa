#ifndef GUARD_IF_CONTROL_TABLE_H
#define GUARD_IF_CONTROL_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class IfControlTable {
public:
    static bool addIfControlVars(StmtNo if_stmt, VarName var);
    static bool isIfControlVars(StmtNo if_stmt, VarName var);
    static ListOfVarNames getIfControlVars(StmtNo if_stmt);
    static ListOfStmtNos getIfControlledByVar(VarName var);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getIfToVarListMap();
    static const std::unordered_map<VarName, ListOfStmtNos>& getVarToIfListMap();
    static void clear();

private:
    static std::unordered_map<StmtNo, ListOfVarNames> ifToVarListMap;
    static std::unordered_map<VarName, ListOfStmtNos> varToIfListMap;
};

#endif // GUARD_IF_CONTROL_TABLE_H
