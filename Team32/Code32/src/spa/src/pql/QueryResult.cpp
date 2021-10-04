#include "QueryResult.h"

using pql::QueryResult;

QueryResult::QueryResult(set<vector<string>> valueResult) : valueResult(valueResult), booleanResult(false), isBooleanSelect(false) {

}

QueryResult::QueryResult(bool booleanResult) : valueResult({}), booleanResult(booleanResult), isBooleanSelect(true){

}