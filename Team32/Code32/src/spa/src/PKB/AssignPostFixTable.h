#ifndef GUARD_ASSIGN_POST_FIX_TABLE_H
#define GUARD_ASSIGN_POST_FIX_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class AssignPostFixTable {
public:
	static bool addPostFix(STMT_NO stmt, string postFix);
	static string getPostFix(STMT_NO stmt);
	static bool isSubString(STMT_NO stmt, string s);
	static unordered_map<STMT_NO, string> getPostFixTable();
	static void clear();
private:
	static unordered_map<STMT_NO, string> postFixMap;
};

#endif // GUARD_ASSIGN_POST_FIX_TABLE_H
