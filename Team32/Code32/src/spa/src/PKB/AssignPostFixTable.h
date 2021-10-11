#ifndef GUARD_ASSIGN_POST_FIX_TABLE_H
#define GUARD_ASSIGN_POST_FIX_TABLE_H

#include "TypePreDefine.h"

#include <string>
#include <unordered_map>

class AssignPostFixTable {
public:
    static bool addPostFix(StmtNo stmt, std::vector<std::string>& postFix);
    static std::vector<std::string> getPostFix(StmtNo stmt);
    static bool isSubExpression(StmtNo stmt, std::vector<std::string>& s);
    static bool isFullExpression(StmtNo stmt, std::vector<std::string>& s);
    static const std::unordered_map<StmtNo, std::vector<std::string>>& getPostFixTable();
    static void clear();
private:
    static std::unordered_map<StmtNo, std::vector<std::string>> postFixMap;
};

#endif // GUARD_ASSIGN_POST_FIX_TABLE_H
