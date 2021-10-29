#ifndef GUARD_IF_CONTROL_TABLE_H
#define GUARD_IF_CONTROL_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class IfControlTable : public Table<StmtNo, VarName> {
public:
    static IfControlTable* getInstance() {
        if (ifcTablePtr == nullptr) {
            ifcTablePtr = new IfControlTable;
        }
        return ifcTablePtr;
    }
    static bool addIfControlVars(StmtNo if_stmt, VarName var);
    static bool isIfControlVars(StmtNo if_stmt, VarName var);
    static ListOfVarNames getIfControlVars(StmtNo if_stmt);
    static ListOfStmtNos getIfControlledByVar(VarName var);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getIfToVarListMap();
    static const std::unordered_map<VarName, ListOfStmtNos>& getVarToIfListMap();
    static void clear();

private:
    //static std::unordered_map<StmtNo, ListOfVarNames> ifToVarListMap;
    //static std::unordered_map<VarName, ListOfStmtNos> varToIfListMap;

    static IfControlTable* ifcTablePtr;
    static inline const size_t IF_TO_VAR_MAP = 1;
    static inline const size_t VAR_TO_IF_MAP = 2;

    IfControlTable() {
        oneToManyMap[IF_TO_VAR_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
        oneToManyRevMap[VAR_TO_IF_MAP] = std::unordered_map<VarName, ListOfStmtNos>();
    }
};

#endif // GUARD_IF_CONTROL_TABLE_H
