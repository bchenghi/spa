#include "QueryProcessorManager.h"
#include "Errors/SemanticError.h"

using pql::QueryProcessorManager;
using pql::PkbAbstractor;
using pql::QueryResultProjector;
using pql::SemanticError;

QueryProcessorManager::QueryProcessorManager() {
    QueryEvaluator queryEvaluator;
    Preprocessor preprocessor;
    QueryResultProjector queryResultProjector;
    this->queryEvaluator = queryEvaluator;
    this->queryPreprocessor = preprocessor;
    this->queryResultProjector = queryResultProjector;
}

void QueryProcessorManager::setOptimisation(bool isOptimisationOn) {
    this->isOptimisationOn = isOptimisationOn;
}

set<string> QueryProcessorManager::executeQuery(std::string queryStr) {
    bool isBooleanSelect = false;
    try {
        isBooleanSelect = queryPreprocessor.checkBooleanSelect(queryStr);
        Query queryObj = queryPreprocessor.preprocess(queryStr);
        QueryResult queryResult = queryEvaluator.executeQuery(queryObj, isOptimisationOn);
        set<string> result = queryResultProjector.createResultSet(queryResult);
        return result;
    } catch(const SemanticError& semanticError) {
        if (isBooleanSelect) {
            return {"FALSE"};
        } else {
            return {};
        }
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
        return {};
    } catch (const char* e) {
        std::cout << e << "\n";
        return {};
    }
}
