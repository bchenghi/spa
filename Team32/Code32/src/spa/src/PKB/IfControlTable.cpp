#include "IfControlTable.h"

IfControlTable* IfControlTable::ifc_table_ptr = nullptr;

bool IfControlTable::addIfControlVars(StmtNo if_stmt, VarName var)
{
    return getInstance()->add_one_to_many(IF_TO_VAR_MAP, if_stmt, var)
        && getInstance()->add_one_to_many_rev(VAR_TO_IF_MAP, var, if_stmt);
}

bool IfControlTable::isIfControlVars(StmtNo if_stmt, VarName var)
{
    return getInstance()->is_one_to_many(IF_TO_VAR_MAP, if_stmt, var);
}

ListOfVarNames IfControlTable::getIfControlVars(StmtNo if_stmt)
{
    return getInstance()->get_one_to_many(IF_TO_VAR_MAP, if_stmt);
}

ListOfStmtNos IfControlTable::getIfControlledByVar(VarName var)
{
    return getInstance()->get_one_to_many_rev(VAR_TO_IF_MAP, var);
}

const std::unordered_map<StmtNo, ListOfVarNames>& IfControlTable::getIfToVarListMap()
{
    return getInstance()->get_one_to_many_map(IF_TO_VAR_MAP);
}

const std::unordered_map<VarName, ListOfStmtNos>& IfControlTable::getVarToIfListMap()
{
    return getInstance()->get_one_to_many_rev_map(VAR_TO_IF_MAP);
}

void IfControlTable::clear() {
    getInstance()->clearAll();
}