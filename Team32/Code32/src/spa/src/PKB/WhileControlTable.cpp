#include "WhileControlTable.h"

WhileControlTable* WhileControlTable::whcTablePtr = nullptr;

bool WhileControlTable::addWhileControlVars(StmtNo while_stmt, VarName var)
{
    return getInstance()->addOneToMany(WHILE_TO_VAR_MAP, while_stmt, var)
        && getInstance()->addOneToManyRev(VAR_TO_WHILE_MAP, var, while_stmt);
}

bool WhileControlTable::isWhileControlVars(StmtNo while_stmt, VarName var)
{
    return getInstance()->isOneToMany(WHILE_TO_VAR_MAP, while_stmt, var);
}

ListOfVarNames WhileControlTable::getWhileControlVars(StmtNo while_stmt)
{
    return getInstance()->getOneToMany(WHILE_TO_VAR_MAP, while_stmt);
}

ListOfStmtNos WhileControlTable::getWhileControlledByVar(VarName var)
{
    return getInstance()->getOneToManyRev(VAR_TO_WHILE_MAP, var);
}

const std::unordered_map<StmtNo, ListOfVarNames>& WhileControlTable::getWhileToVarListMap()
{
    return getInstance()->getOneToManyMap(WHILE_TO_VAR_MAP);
}

const std::unordered_map<VarName, ListOfStmtNos>& WhileControlTable::getVarToWhileListMap()
{
    return getInstance()->getOneToManyRevMap(VAR_TO_WHILE_MAP);
}

void WhileControlTable::clear() {
    getInstance()->clearAll();
}