#ifndef GUARD_PROC_TABLE_H
#define GUARD_PROC_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ProcTable : public Table<ProcName, StmtNo> {
public:
    static ProcTable* getInstance() {
        if (proc_table_ptr == nullptr) {
            proc_table_ptr = new ProcTable;
        }
        return proc_table_ptr;
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
    static ProcTable* proc_table_ptr;
    static inline const size_t PROC_STMT_MAP = 1;

    ProcTable() {
        one_to_many_map[PROC_STMT_MAP] = std::unordered_map<ProcName, ListOfStmtNos>();
    }
};

#endif // GUARD_PROC_TABLE_H
