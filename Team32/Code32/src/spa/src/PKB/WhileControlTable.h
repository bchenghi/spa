#ifndef GUARD_WHILE_CONTROL_TABLE_H
#define GUARD_WHILE_CONTROL_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class WhileControlTable : public Table<StmtNo, VarName> {
public:
    static WhileControlTable* getInstance() {
        if (whc_table_ptr == nullptr) {
            whc_table_ptr = new WhileControlTable;
        }
        return whc_table_ptr;
    }
    static bool addWhileControlVars(StmtNo while_stmt, VarName var);
    static bool isWhileControlVars(StmtNo while_stmt, VarName var);
    static ListOfVarNames getWhileControlVars(StmtNo while_stmt);
    static ListOfStmtNos getWhileControlledByVar(VarName var);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getWhileToVarListMap();
    static const std::unordered_map<VarName, ListOfStmtNos>& getVarToWhileListMap();
    static void clear();

private:
    //static std::unordered_map<StmtNo, ListOfVarNames> whileToVarListMap;
    //static std::unordered_map<VarName, ListOfStmtNos> varToWhileListMap;

    static WhileControlTable* whc_table_ptr;
    static const size_t WHILE_TO_VAR_MAP = 1;
    static const size_t VAR_TO_WHILE_MAP = 3;

    WhileControlTable() {
        one_to_many_map[WHILE_TO_VAR_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
        one_to_many_rev_map[VAR_TO_WHILE_MAP] = std::unordered_map<VarName, ListOfStmtNos>();
    }
};

#endif // GUARD_WHILE_CONTROL_TABLE_H
