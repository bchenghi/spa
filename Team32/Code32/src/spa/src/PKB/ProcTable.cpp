#include "ProcTable.h"

ListOfProcNames ProcTable::procNameList;
int ProcTable::size = 0;
ProcTable* ProcTable::proc_table_ptr = nullptr;

bool ProcTable::addProc(ProcName procName, ListOfStmtNos stmtNumList)
{
    ProcTable::size++;
    ProcTable::procNameList.insert(procName);
    return getInstance()->add_one_to_many(PROC_STMT_MAP, procName, stmtNumList);
}

ListOfStmtNos ProcTable::getProcStmtList(ProcName procName)
{
    return getInstance()->get_one_to_many(PROC_STMT_MAP, procName);
}

ListOfProcNames ProcTable::getAllProcedure()
{
    return ProcTable::procNameList;
}

int ProcTable::getSize()
{
    return ProcTable::size;
}

void ProcTable::clear()
{
    getInstance()->clearAll();
    procNameList.clear();
    size = 0;
}
