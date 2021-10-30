#include "IfControlTable.h"

IfControlTable* IfControlTable::ifcTablePtr = nullptr;

bool IfControlTable::addIfControlVars(StmtNo if_stmt, VarName var)
{
    return getInstance()->addOneToMany(IF_TO_VAR_MAP, if_stmt, var)
        && getInstance()->addOneToManyRev(VAR_TO_IF_MAP, var, if_stmt);
}

bool IfControlTable::isIfControlVars(StmtNo if_stmt, VarName var)
{
    return getInstance()->isOneToMany(IF_TO_VAR_MAP, if_stmt, var);
}

ListOfVarNames IfControlTable::getIfControlVars(StmtNo if_stmt)
{
    return getInstance()->getOneToMany(IF_TO_VAR_MAP, if_stmt);
}

ListOfStmtNos IfControlTable::getIfControlledByVar(VarName var)
{
    return getInstance()->getOneToManyRev(VAR_TO_IF_MAP, var);
}

const std::unordered_map<StmtNo, ListOfVarNames>& IfControlTable::getIfToVarListMap()
{
    return getInstance()->getOneToManyMap(IF_TO_VAR_MAP);
}

const std::unordered_map<VarName, ListOfStmtNos>& IfControlTable::getVarToIfListMap()
{
    return getInstance()->getOneToManyRevMap(VAR_TO_IF_MAP);
}

void IfControlTable::clear() {
    getInstance()->clearAll();
}