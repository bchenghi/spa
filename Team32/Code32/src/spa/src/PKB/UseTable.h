#ifndef GUARD_USE_TABLE_H
#define GUARD_USE_TABLE_H

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

class UseTable {
public:
    static bool addStmtUse(STMT_NO stmtNo, VAR_NAME varName);
    static bool addProcUse(PROC_NAME procName, VAR_NAME varName);
    static bool isStmtUse(STMT_NO stmtNo, VAR_NAME varName);
    static bool isProcUse(PROC_NAME procName, VAR_NAME varName);
    static unordered_set<VAR_NAME> getStmtUse(STMT_NO stmtNo);
    static unordered_set<VAR_NAME> getProcUse(PROC_NAME procName);

private:
    static unordered_map<STMT_NO, unordered_set<VAR_NAME>> stmtUseMap;
    static unordered_map<PROC_NAME, unordered_set<VAR_NAME>> procUseMap;
};

#endif // GUARD_USE_TABLE_H