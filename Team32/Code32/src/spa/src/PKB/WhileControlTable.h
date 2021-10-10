#ifndef GUARD_WHILE_CONTROL_TABLE_H
#define GUARD_WHILE_CONTROL_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class WhileControlTable {
public:
    static bool addWhileControlVars(StmtNo while_stmt, VarName var);
    static bool isWhileControlVars(StmtNo while_stmt, VarName var);
    static ListOfVarNames getWhileControlVars(StmtNo while_stmt);
    static ListOfStmtNos getWhileControlledByVar(VarName var);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getWhileToVarListMap();
    static const std::unordered_map<VarName, ListOfStmtNos>& getVarToWhileListMap();
    static void clear();

private:
    static std::unordered_map<StmtNo, ListOfVarNames> whileToVarListMap;
    static std::unordered_map<VarName, ListOfStmtNos> varToWhileListMap;
};

#endif // GUARD_WHILE_CONTROL_TABLE_H
