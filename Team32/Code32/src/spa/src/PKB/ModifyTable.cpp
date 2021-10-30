#include "ModifyTable.h"

ModifyPTable* ModifyPTable::modPTablePtr = nullptr;
ModifySTable* ModifySTable::modSTablePtr = nullptr;
ModifyPTable* ModifyTable::modPTable = ModifyPTable::getInstance();
ModifySTable* ModifyTable::modSTable = ModifySTable::getInstance();

bool ModifyTable::addStmtModify(StmtNo stmt, VarName varName)
{
    return modSTable->addModify(stmt, varName);
}

bool ModifyTable::addProcModify(ProcName procName, VarName varName)
{
    return modPTable->addModify(procName, varName);
}

bool ModifyTable::isStmtModify(StmtNo stmt, VarName varName)
{
    return modSTable->isModify(stmt, varName);
}

bool ModifyTable::isProcModify(ProcName procName, VarName varName)
{
    return modPTable->isModify(procName, varName);
}

ListOfVarNames ModifyTable::getStmtModify(StmtNo stmt)
{
    return modSTable->getModify(stmt);
}

ListOfVarNames ModifyTable::getProcModify(ProcName procName)
{
    return modPTable->getModify(procName);
}

const std::unordered_map<StmtNo, ListOfVarNames>& ModifyTable::getStmtModifyMap()
{
    return modSTable->getModifyMap();
}

const std::unordered_map<ProcName, ListOfVarNames>& ModifyTable::getProcModifyMap()
{
    return modPTable->getModifyMap();
}

void ModifyTable::clear()
{
    modSTable->clear();
    modPTable->clear();
}
