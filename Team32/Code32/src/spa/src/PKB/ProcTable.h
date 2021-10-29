#ifndef GUARD_PROC_TABLE_H
#define GUARD_PROC_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ProcTable : public Table<ProcName, StmtNo> {
public:
    static ProcTable* getInstance() {
        if (procTablePtr == nullptr) {
            procTablePtr = new ProcTable;
        }
        return procTablePtr;
    }
    static bool addProc(ProcName procName, ListOfStmtNos stmtNumList);
    static ListOfStmtNos getProcStmtList(ProcName procName);
    static ListOfProcNames getAllProcedure();
    static int getSize();
    static void clear();

private:
    //static std::unordered_map<ProcName, ListOfStmtNos> nameToStmtListMap;

    static ListOfProcNames procNameList;
    static int size;
    static ProcTable* procTablePtr;
    static inline const size_t PROC_STMT_MAP = 1;

    ProcTable() {
        oneToManyMap[PROC_STMT_MAP] = std::unordered_map<ProcName, ListOfStmtNos>();
    }
};

#endif // GUARD_PROC_TABLE_H
