#include "UseTable.h"

UsePTable* UsePTable::usePTablePtr = nullptr;
UseSTable* UseSTable::useSTablePtr = nullptr;
UsePTable* UseTable::usePTable = UsePTable::getInstance();
UseSTable* UseTable::useSTable = UseSTable::getInstance();

bool UseTable::addStmtUse(StmtNo stmt, VarName varName)
{
    return useSTable->addUse(stmt, varName);
}

bool UseTable::addProcUse(ProcName procName, VarName varName)
{
    return usePTable->addUse(procName, varName);
}

bool UseTable::isStmtUse(StmtNo stmt, VarName varName)
{
    return useSTable->isUse(stmt, varName);
}

bool UseTable::isProcUse(ProcName procName, VarName varName)
{
    return usePTable->isUse(procName, varName);
}

ListOfVarNames UseTable::getStmtUse(StmtNo stmt)
{
    return useSTable->getUse(stmt);
}

ListOfVarNames UseTable::getProcUse(ProcName procName)
{
    return usePTable->getUse(procName);
}

const std::unordered_map<StmtNo, ListOfVarNames> & UseTable::getStmtUseMap() {
    return useSTable->getUseMap();
}

const std::unordered_map<ProcName, ListOfVarNames> & UseTable::getProcUseMap() {
    return usePTable->getUseMap();
}

void UseTable::clear()
{
    useSTable->clear();
    usePTable->clear();
}
