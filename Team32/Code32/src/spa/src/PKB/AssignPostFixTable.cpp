#include "AssignPostFixTable.h"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

unordered_map<STMT_NO, vector<string>> AssignPostFixTable::postFixMap;

bool AssignPostFixTable::addPostFix(STMT_NO stmt, vector<string>& postFix)
{
	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		throw "Already has a postfix.";
	}
	else {
		AssignPostFixTable::postFixMap[stmt] = postFix;
		return true;
	}
}

vector<string> AssignPostFixTable::getPostFix(STMT_NO stmt)
{
	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		return res->second;
	}
	else {
		return {};
	}
}

bool isSubVector(vector<string>& v1, vector<string>& v2)
{
    vector<string>::const_iterator v1_iter = v1.begin(), v2_iter = v2.begin();

    while (v1_iter != v1.end()) {
        if (*v1_iter == *v2_iter) break;

        v1_iter++;
    }

    while (v1_iter != v1.end() && v2_iter != v2.end()) {
        if (*v1_iter != *v2_iter) return false;

        v1_iter++;
        v2_iter++;
    }

    return v2_iter == v2.end();
}

bool AssignPostFixTable::isSubExpression(STMT_NO stmt, vector<string>& s)
{
    if (s.empty()) return true;

	auto res = AssignPostFixTable::postFixMap.find(stmt);
	if (res != AssignPostFixTable::postFixMap.end()) {
		vector<string> postfix = res->second;

        return isSubVector(postfix, s);
	}
	else {
		return false;
	}
}

const unordered_map<STMT_NO, vector<string>>& AssignPostFixTable::getPostFixTable() {
    return postFixMap;
}

void AssignPostFixTable::clear() {
    postFixMap.clear();
}
