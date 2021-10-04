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
        QueryResult queryResult = queryEvaluator.executeQuery(queryObj);
        if (queryResult.isBooleanSelect) {
            if (queryResult.booleanResult) {
                return {"TRUE"};
            } else {
                return {"FALSE"};
            }
        } else {
            set<string> result = {};
            for (vector<string> listOfValidValues : queryResult.valueResult) {
                string validValuesStr;
                for (int i = 0; i < listOfValidValues.size(); i++) {
                    validValuesStr += listOfValidValues[i];
                    if (i == listOfValidValues.size() - 1) {
                        break;
                    }
                    validValuesStr += " ";
                }
                result.insert(validValuesStr);
            }
            return result;
        }
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
        return {};
    } catch (const char* e) {
        std::cout << e << "\n";
        return {};
    }
}
