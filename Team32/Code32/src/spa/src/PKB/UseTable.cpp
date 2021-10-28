#include "UseTable.h"

UsePTable* UsePTable::use_p_table_ptr = nullptr;
UseSTable* UseSTable::use_s_table_ptr = nullptr;
UsePTable* UseTable::use_p_table = UsePTable::getInstance();
UseSTable* UseTable::use_s_table = UseSTable::getInstance();

bool UseTable::addStmtUse(StmtNo stmt, VarName varName)
{
    return use_s_table->addUse(stmt, varName);
}

bool UseTable::addProcUse(ProcName procName, VarName varName)
{
    return use_p_table->addUse(procName, varName);
}

bool UseTable::isStmtUse(StmtNo stmt, VarName varName)
{
    return use_s_table->isUse(stmt, varName);
}

bool UseTable::isProcUse(ProcName procName, VarName varName)
{
    return use_p_table->isUse(procName, varName);
}

ListOfVarNames UseTable::getStmtUse(StmtNo stmt)
{
    return use_s_table->getUse(stmt);
}

ListOfVarNames UseTable::getProcUse(ProcName procName)
{
    return use_p_table->getUse(procName);
}

const std::unordered_map<StmtNo, ListOfVarNames> & UseTable::getStmtUseMap() {
    return use_s_table->getUseMap();
}

const std::unordered_map<ProcName, ListOfVarNames> & UseTable::getProcUseMap() {
    return use_p_table->getUseMap();
}

void UseTable::clear()
{
    use_s_table->clear();
    use_p_table->clear();
}
