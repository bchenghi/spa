#include "WhileControlTable.h"

WhileControlTable* WhileControlTable::whc_table_ptr = nullptr;

bool WhileControlTable::addWhileControlVars(StmtNo while_stmt, VarName var)
{
    return getInstance()->add_one_to_many(WHILE_TO_VAR_MAP, while_stmt, var)
        && getInstance()->add_one_to_many_rev(VAR_TO_WHILE_MAP, var, while_stmt);
}

bool WhileControlTable::isWhileControlVars(StmtNo while_stmt, VarName var)
{
    return getInstance()->is_one_to_many(WHILE_TO_VAR_MAP, while_stmt, var);
}

ListOfVarNames WhileControlTable::getWhileControlVars(StmtNo while_stmt)
{
    return getInstance()->get_one_to_many(WHILE_TO_VAR_MAP, while_stmt);
}

ListOfStmtNos WhileControlTable::getWhileControlledByVar(VarName var)
{
    return getInstance()->get_one_to_many_rev(VAR_TO_WHILE_MAP, var);
}

const std::unordered_map<StmtNo, ListOfVarNames>& WhileControlTable::getWhileToVarListMap()
{
    return getInstance()->get_one_to_many_map(WHILE_TO_VAR_MAP);
}

const std::unordered_map<VarName, ListOfStmtNos>& WhileControlTable::getVarToWhileListMap()
{
    return getInstance()->get_one_to_many_rev_map(VAR_TO_WHILE_MAP);
}

void WhileControlTable::clear() {
    getInstance()->clearAll();
}