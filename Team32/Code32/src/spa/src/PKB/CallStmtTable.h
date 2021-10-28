#ifndef GUARD_CALL_STMT_TABLE_H
#define GUARD_CALL_STMT_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class CallStmtTable : public Table<StmtNo, ProcName> {
public:
    static CallStmtTable* getInstance() {
        if (callstmt_table_ptr == nullptr) {
            callstmt_table_ptr = new CallStmtTable;
        }
        return callstmt_table_ptr;
    }
    static bool insert(StmtNo, const ProcName&);
    static ProcName getProcCalled(StmtNo);
    static ListOfStmtNos getCallStmtsOfProcCalled(const ProcName&);
    static const std::unordered_map<StmtNo, ProcName> & getCallStmtToProcMap();
    static const std::unordered_map<ProcName, ListOfStmtNos> & getProcToCallStmtsMap();
    static void clear();
private:
    //static std::unordered_map<StmtNo, ProcName> callStmtToProcMap;
    //static std::unordered_map<ProcName, ListOfStmtNos> procToCallStmtsMap;

    static CallStmtTable* callstmt_table_ptr;
    static inline const size_t CALL_PROC_MAP = 1;
    static inline const size_t PROC_CALL_MAP = 233;

    CallStmtTable() {
        one_to_one_map[CALL_PROC_MAP] = std::unordered_map<StmtNo, ProcName>();
        one_to_many_rev_map[PROC_CALL_MAP] = std::unordered_map<ProcName, ListOfStmtNos>();
    }
};

#endif
