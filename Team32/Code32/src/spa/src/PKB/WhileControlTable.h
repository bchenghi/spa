#ifndef GUARD_WHILE_CONTROL_TABLE_H
#define GUARD_WHILE_CONTROL_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class WhileControlTable : public Table<StmtNo, VarName> {
public:
    static WhileControlTable* getInstance() {
        if (whcTablePtr == nullptr) {
            whcTablePtr = new WhileControlTable;
        }
        return whcTablePtr;
    }
    static bool addWhileControlVars(StmtNo while_stmt, VarName var);
    static bool isWhileControlVars(StmtNo while_stmt, VarName var);
    static ListOfVarNames getWhileControlVars(StmtNo while_stmt);
    static ListOfStmtNos getWhileControlledByVar(VarName var);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getWhileToVarListMap();
    static const std::unordered_map<VarName, ListOfStmtNos>& getVarToWhileListMap();
    static void clear();

private:
    static WhileControlTable* whcTablePtr;
    static inline const size_t WHILE_TO_VAR_MAP = 1;
    static inline const size_t VAR_TO_WHILE_MAP = 2;

    WhileControlTable() {
        oneToManyMap[WHILE_TO_VAR_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
        oneToManyRevMap[VAR_TO_WHILE_MAP] = std::unordered_map<VarName, ListOfStmtNos>();
    }
};

#endif
