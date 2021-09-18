#include "ProcTable.h"

std::unordered_map<ProcName, ListOfStmtNos> ProcTable::nameToStmtListMap;
ListOfProcNames ProcTable::procNameList;
int ProcTable::size = 0;

bool ProcTable::addProc(ProcName procName, ListOfStmtNos stmtNumList)
{
    auto res = ProcTable::nameToStmtListMap.find(procName);
    if (res != ProcTable::nameToStmtListMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        ProcTable::nameToStmtListMap[procName] = stmtNumList;
        ProcTable::procNameList.push_back(procName);
        ProcTable::size++;
    }
    return false;
}

ListOfStmtNos ProcTable::getProcStmtList(ProcName procName)
{
    auto res = ProcTable::nameToStmtListMap.find(procName);
    if (res != ProcTable::nameToStmtListMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
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
    procNameList.clear();
    nameToStmtListMap.clear();
    size = 0;
}
