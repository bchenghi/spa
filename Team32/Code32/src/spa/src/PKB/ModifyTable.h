
#ifndef GUARD_MODIFY_TABLE_H
#define GUARD_MODIFY_TABLE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

using std::string;
using std::unordered_map;
using std::unordered_set;

typedef string VAR_NAME;
typedef string PROC_NAME;
typedef int STMT_NO;

class ModifyTable {
public:
    static bool addStmtModify(STMT_NO stmtNo, VAR_NAME varName);
    static bool addProcModify(PROC_NAME procName, VAR_NAME varName);
    static bool isStmtModify(STMT_NO stmtNo, VAR_NAME varName);
    static bool isProcModify(PROC_NAME procName, VAR_NAME varName);
    static unordered_set<VAR_NAME> getStmtModify(STMT_NO stmtNo);
    static unordered_set<VAR_NAME> getProcModify(PROC_NAME procName);

private:
    static unordered_map<STMT_NO, unordered_set<VAR_NAME>> stmtModifyMap;
    static unordered_map<PROC_NAME, unordered_set<VAR_NAME>> procModifyMap;
};

#endif // GUARD_MODIFY_TABLE_H