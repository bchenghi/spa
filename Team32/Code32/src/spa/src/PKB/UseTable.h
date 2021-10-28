#ifndef GUARD_USE_TABLE_H
#define GUARD_USE_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class UseSTable : public Table<StmtNo, VarName> {
public:
    static UseSTable* getInstance() {
        if (use_s_table_ptr == nullptr) {
            use_s_table_ptr = new UseSTable;
        }
        return use_s_table_ptr;
    }
    bool addUse(StmtNo stmt, VarName var) {
        return add_one_to_many(STMT_USE_MAP, stmt, var);
    }
    bool isUse(StmtNo stmt, VarName var) {
        return is_one_to_many(STMT_USE_MAP, stmt, var);
    }
    ListOfVarNames getUse(StmtNo stmt) {
        return get_one_to_many(STMT_USE_MAP, stmt);
    }
    const std::unordered_map<StmtNo, ListOfVarNames>& getUseMap() {
        return get_one_to_many_map(STMT_USE_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static UseSTable* use_s_table_ptr;
    static const size_t STMT_USE_MAP = 1;

    UseSTable() {
        one_to_many_map[STMT_USE_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
    }
};

class UsePTable : public Table<ProcName, VarName> {
public:
    static UsePTable* getInstance() {
        if (use_p_table_ptr == nullptr) {
            use_p_table_ptr = new UsePTable;
        }
        return use_p_table_ptr;
    }
    bool addUse(ProcName proc, VarName var) {
        return add_one_to_many(PROC_USE_MAP, proc, var);
    }
    bool isUse(ProcName proc, VarName var) {
        return is_one_to_many(PROC_USE_MAP, proc, var);
    }
    ListOfVarNames getUse(ProcName proc) {
        return get_one_to_many(PROC_USE_MAP, proc);
    }
    const std::unordered_map<ProcName, ListOfVarNames>& getUseMap() {
        return get_one_to_many_map(PROC_USE_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static UsePTable* use_p_table_ptr;
    static const size_t PROC_USE_MAP = 1;

    UsePTable() {
        one_to_many_map[PROC_USE_MAP] = std::unordered_map<ProcName, ListOfVarNames>();
    }
};

//UsePTable* UsePTable::use_p_table_ptr = nullptr;
//UseSTable* UseSTable::use_s_table_ptr = nullptr;

class UseTable {
public:
    static bool addStmtUse(StmtNo stmt, VarName varName);
    static bool addProcUse(ProcName procName, VarName varName);
    static bool isStmtUse(StmtNo stmt, VarName varName);
    static bool isProcUse(ProcName procName, VarName varName);
    static ListOfVarNames getStmtUse(StmtNo stmt);
    static ListOfVarNames getProcUse(ProcName procName);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getStmtUseMap();
    static const std::unordered_map<ProcName, ListOfVarNames>& getProcUseMap();
    static void clear();

private:
    static UsePTable* use_p_table;
    static UseSTable* use_s_table;
};

#endif // GUARD_USE_TABLE_H
