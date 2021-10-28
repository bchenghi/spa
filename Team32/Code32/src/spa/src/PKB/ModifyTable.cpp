#include "ModifyTable.h"

ModifyPTable* ModifyPTable::mod_p_table_ptr = nullptr;
ModifySTable* ModifySTable::mod_s_table_ptr = nullptr;
ModifyPTable* ModifyTable::mod_p_table = ModifyPTable::getInstance();
ModifySTable* ModifyTable::mod_s_table = ModifySTable::getInstance();

bool ModifyTable::addStmtModify(StmtNo stmt, VarName varName)
{
    return mod_s_table->addModify(stmt, varName);
}

bool ModifyTable::addProcModify(ProcName procName, VarName varName)
{
    return mod_p_table->addModify(procName, varName);
}

bool ModifyTable::isStmtModify(StmtNo stmt, VarName varName)
{
    return mod_s_table->isModify(stmt, varName);
}

bool ModifyTable::isProcModify(ProcName procName, VarName varName)
{
    return mod_p_table->isModify(procName, varName);
}

ListOfVarNames ModifyTable::getStmtModify(StmtNo stmt)
{
    return mod_s_table->getModify(stmt);
}

ListOfVarNames ModifyTable::getProcModify(ProcName procName)
{
    return mod_p_table->getModify(procName);
}

const std::unordered_map<StmtNo, ListOfVarNames>& ModifyTable::getStmtModifyMap()
{
    return mod_s_table->getModifyMap();
}

const std::unordered_map<ProcName, ListOfVarNames>& ModifyTable::getProcModifyMap()
{
    return mod_p_table->getModifyMap();
}

void ModifyTable::clear()
{
    mod_s_table->clear();
    mod_p_table->clear();
}
