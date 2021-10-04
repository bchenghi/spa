#include "QueryEvaluatorResult.h"

using pql::QueryEvaluatorResult;

QueryEvaluatorResult::QueryEvaluatorResult(vector<unordered_map<QueryDesignEntity, QueryArgValue>> entityValuesList) :
entityValuesList(entityValuesList), isValid(true) {

}

QueryEvaluatorResult::QueryEvaluatorResult(bool isValid) :
entityValuesList({}), isValid(isValid) {

}
