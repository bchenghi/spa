#include "QueryProcessorManager.h"

using pql::QueryProcessorManager;
using pql::PkbAbstractor;
using pql::QueryResultProjector;

QueryProcessorManager::QueryProcessorManager() {
    QueryEvaluator queryEvaluator;
    Preprocessor preprocessor;
    this->queryEvaluator = queryEvaluator;
    this->queryPreprocessor = preprocessor;
}

set<string> QueryProcessorManager::executeQuery(std::string queryStr) {
    try {
        Query queryObj = queryPreprocessor.preprocess(queryStr);
        return queryEvaluator.executeQuery(queryObj);
    } catch (const char* e) {
        std::cout << e << "\n";
        return {};
    }
}
