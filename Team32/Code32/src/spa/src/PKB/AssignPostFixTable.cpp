#include "AssignPostFixTable.h"

unordered_map<STMT_NO, string> AssignPostFixTable::postFixMap;

bool AssignPostFixTable::addPostFix(STMT_NO stmt, string postFix)
{
	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		throw "Already has a postfix.";
	}
	else {
		AssignPostFixTable::postFixMap[stmt] = postFix;
		return true;
	}
	return false;
}

string AssignPostFixTable::getPostFix(STMT_NO stmt)
{
	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		return res->second;
	}
	else {
		return string();
	}
	return string();
}

bool AssignPostFixTable::isSubString(STMT_NO stmt, string s)
{
	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		string postfix = res->second;
		string::size_type pos = postfix.find(s);
		if (pos != postfix.npos) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return false;
}
