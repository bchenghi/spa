#include "QueryProcessorManager.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/QueryResultProjector/QueryResultProjector.h"

using pql::QueryProcessorManager;
using pql::PkbAbstractor;
using pql::QueryResultProjector;

QueryProcessorManager::QueryProcessorManager() {
    this->queryEvaluator = QueryEvaluator();
    this->queryPreprocessor = Preprocessor();
}

void QueryProcessorManager::executeQuery(std::string& queryStr) {
    Query queryObj = queryPreprocessor.preprocess(queryStr);
    queryEvaluator.executeQuery(queryObj);
}