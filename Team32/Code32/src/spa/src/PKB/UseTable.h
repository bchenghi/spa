#ifndef GUARD_USE_TABLE_H
#define GUARD_USE_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class UseSTable : public Table<StmtNo, VarName> {
public:
    static UseSTable* getInstance() {
        if (useSTablePtr == nullptr) {
            useSTablePtr = new UseSTable;
        }
        return useSTablePtr;
    }
    bool addUse(StmtNo stmt, VarName var) {
        return addOneToMany(STMT_USE_MAP, stmt, var);
    }
    bool isUse(StmtNo stmt, VarName var) {
        return isOneToMany(STMT_USE_MAP, stmt, var);
    }
    ListOfVarNames getUse(StmtNo stmt) {
        return getOneToMany(STMT_USE_MAP, stmt);
    }
    const std::unordered_map<StmtNo, ListOfVarNames>& getUseMap() {
        return getOneToManyMap(STMT_USE_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static UseSTable* useSTablePtr;
    static inline const size_t STMT_USE_MAP = 1;

    UseSTable() {
        oneToManyMap[STMT_USE_MAP] = std::unordered_map<StmtNo, ListOfVarNames>();
    }
};

class UsePTable : public Table<ProcName, VarName> {
public:
    static UsePTable* getInstance() {
        if (usePTablePtr == nullptr) {
            usePTablePtr = new UsePTable;
        }
        return usePTablePtr;
    }
    bool addUse(ProcName proc, VarName var) {
        return addOneToMany(PROC_USE_MAP, proc, var);
    }
    bool isUse(ProcName proc, VarName var) {
        return isOneToMany(PROC_USE_MAP, proc, var);
    }
    ListOfVarNames getUse(ProcName proc) {
        return getOneToMany(PROC_USE_MAP, proc);
    }
    const std::unordered_map<ProcName, ListOfVarNames>& getUseMap() {
        return getOneToManyMap(PROC_USE_MAP);
    }
    void clear() {
        clearAll();
    }
private:
    static UsePTable* usePTablePtr;
    static inline const size_t PROC_USE_MAP = 1;

    UsePTable() {
        oneToManyMap[PROC_USE_MAP] = std::unordered_map<ProcName, ListOfVarNames>();
    }
};

//UsePTable* UsePTable::usePTablePtr = nullptr;
//UseSTable* UseSTable::useSTablePtr = nullptr;

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
    static UsePTable* usePTable;
    static UseSTable* useSTable;
};

#endif // GUARD_USE_TABLE_H
