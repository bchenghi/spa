#include "ProcTable.h"

ListOfProcNames ProcTable::procNameList;
int ProcTable::size = 0;
ProcTable* ProcTable::procTablePtr = nullptr;

bool ProcTable::addProc(ProcName procName, ListOfStmtNos stmtNumList)
{
    ProcTable::size++;
    ProcTable::procNameList.insert(procName);
    return getInstance()->addOneToMany(PROC_STMT_MAP, procName, stmtNumList);
}

ListOfStmtNos ProcTable::getProcStmtList(ProcName procName)
{
    return getInstance()->getOneToMany(PROC_STMT_MAP, procName);
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
