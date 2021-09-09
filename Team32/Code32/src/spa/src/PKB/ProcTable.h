#ifndef GUARD_PROC_TABLE_H
#define GUARD_PROC_TABLE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

using std::unordered_map;
using std::vector;
using std::string;

typedef string PROC_NAME;
typedef vector<string> LIST_OF_PROC_NAME;
typedef unordered_set<int> LIST_OF_STMT_NO;

class ProcTable {
public:
    static bool addProc(PROC_NAME procName, LIST_OF_STMT_NO stmtNoList);
    static LIST_OF_STMT_NO getProcStmtList(PROC_NAME procName);
    static LIST_OF_PROC_NAME getAllProcedure();
    static int getSize();

private:
    static unordered_map<PROC_NAME, LIST_OF_STMT_NO> nameToStmtListMap;
    static LIST_OF_PROC_NAME procNameList;
    static int size;
};

int ProcTable::size = 0;

#endif // GUARD_PROC_TABLE_H