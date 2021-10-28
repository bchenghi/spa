#ifndef GUARD_MODIFY_TABLE_H
#define GUARD_MODIFY_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ModifySTable : public Table<StmtNo, VarName> {
public:
    static ModifySTable* getInstance() {
        if (mod_s_table_ptr == nullptr) {
            mod_s_table_ptr = new ModifySTable;
        }
        return mod_s_table_ptr;
    }
    bool addModify(StmtNo stmt, VarName var) {
        return add_one_to_many(STMT_MOD_MAP, stmt, var);
    }
    bool isModify(StmtNo stmt, VarName var) {
        return is_one_to_many(STMT_MOD_MAP, stmt, var);
    }
    ListOfVarNames getModify(StmtNo stmt) {
        return get_one_to_many(STMT_MOD_MAP, stmt);
    }
    const std::unordered_map<StmtNo, ListOfVarNames>& getModifyMap() {
        return get_one_to_many_map(STMT_MOD_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static ModifySTable* mod_s_table_ptr;
    static const size_t STMT_MOD_MAP = 1;

    ModifySTable() {
        one_to_many_map[STMT_MOD_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
    }
};

class ModifyPTable : public Table<ProcName, VarName> {
public:
    static ModifyPTable* getInstance() {
        if (mod_p_table_ptr == nullptr) {
            mod_p_table_ptr = new ModifyPTable;
        }
        return mod_p_table_ptr;
    }
    bool addModify(ProcName proc, VarName var) {
        return add_one_to_many(PROC_MOD_MAP, proc, var);
    }
    bool isModify(ProcName proc, VarName var) {
        return is_one_to_many(PROC_MOD_MAP, proc, var);
    }
    ListOfVarNames getModify(ProcName proc) {
        return get_one_to_many(PROC_MOD_MAP, proc);
    }
    const std::unordered_map<ProcName, ListOfVarNames>& getModifyMap() {
        return get_one_to_many_map(PROC_MOD_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static ModifyPTable* mod_p_table_ptr;
    static const size_t PROC_MOD_MAP = 1;

    ModifyPTable() {
        one_to_many_map[PROC_MOD_MAP] = std::unordered_map<ProcName, ListOfVarNames>();
    }
};

class ModifyTable {
public:
    static bool addStmtModify(StmtNo stmt, VarName varName);
    static bool addProcModify(ProcName procName, VarName varName);
    static bool isStmtModify(StmtNo stmt, VarName varName);
    static bool isProcModify(ProcName procName, VarName varName);
    static ListOfVarNames getStmtModify(StmtNo stmt);
    static ListOfVarNames getProcModify(ProcName procName);
    static const std::unordered_map<StmtNo, ListOfVarNames>& getStmtModifyMap();
    static const std::unordered_map<ProcName, ListOfVarNames>& getProcModifyMap();
    static void clear();

private:
    static ModifyPTable* mod_p_table;
    static ModifySTable* mod_s_table;
};

#endif // GUARD_MODIFY_TABLE_H
