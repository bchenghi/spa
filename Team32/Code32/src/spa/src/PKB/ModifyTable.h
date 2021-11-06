#ifndef GUARD_MODIFY_TABLE_H
#define GUARD_MODIFY_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ModifySTable : public Table<StmtNo, VarName> {
public:
    static ModifySTable* getInstance() {
        if (modSTablePtr == nullptr) {
            modSTablePtr = new ModifySTable;
        }
        return modSTablePtr;
    }
    bool addModify(StmtNo stmt, VarName var) {
        return addOneToMany(STMT_MOD_MAP, stmt, var);
    }
    bool isModify(StmtNo stmt, VarName var) {
        return isOneToMany(STMT_MOD_MAP, stmt, var);
    }
    ListOfVarNames getModify(StmtNo stmt) {
        return getOneToMany(STMT_MOD_MAP, stmt);
    }
    const std::unordered_map<StmtNo, ListOfVarNames>& getModifyMap() {
        return getOneToManyMap(STMT_MOD_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static ModifySTable* modSTablePtr;
    static inline const size_t STMT_MOD_MAP = 1;

    ModifySTable() {
        oneToManyMap[STMT_MOD_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
    }
};

class ModifyPTable : public Table<ProcName, VarName> {
public:
    static ModifyPTable* getInstance() {
        if (modPTablePtr == nullptr) {
            modPTablePtr = new ModifyPTable;
        }
        return modPTablePtr;
    }
    bool addModify(ProcName proc, VarName var) {
        return addOneToMany(PROC_MOD_MAP, proc, var);
    }
    bool isModify(ProcName proc, VarName var) {
        return isOneToMany(PROC_MOD_MAP, proc, var);
    }
    ListOfVarNames getModify(ProcName proc) {
        return getOneToMany(PROC_MOD_MAP, proc);
    }
    const std::unordered_map<ProcName, ListOfVarNames>& getModifyMap() {
        return getOneToManyMap(PROC_MOD_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static ModifyPTable* modPTablePtr;
    static inline const size_t PROC_MOD_MAP = 1;

    ModifyPTable() {
        oneToManyMap[PROC_MOD_MAP] = std::unordered_map<ProcName, ListOfVarNames>();
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
    static ModifyPTable* modPTable;
    static ModifySTable* modSTable;
};

#endif
