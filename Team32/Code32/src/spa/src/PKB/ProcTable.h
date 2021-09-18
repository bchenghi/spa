#ifndef GUARD_PROC_TABLE_H
#define GUARD_PROC_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class ProcTable {
public:
    static bool addProc(ProcName procName, ListOfStmtNos stmtNumList);
    static ListOfStmtNos getProcStmtList(ProcName procName);
    static ListOfProcNames getAllProcedure();
    static int getSize();
    static void clear();

private:
    static std::unordered_map<ProcName, ListOfStmtNos> nameToStmtListMap;
    static ListOfProcNames procNameList;
    static int size;
};

#endif // GUARD_PROC_TABLE_H
