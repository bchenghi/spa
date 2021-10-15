#include "QueryProcessorManager.h"
#include "Errors/SemanticError.h"

using pql::QueryProcessorManager;
using pql::PkbAbstractor;
using pql::QueryResultProjector;
using pql::SemanticError;

QueryProcessorManager::QueryProcessorManager() {
    QueryEvaluator queryEvaluator;
    Preprocessor preprocessor;
    this->queryEvaluator = queryEvaluator;
    this->queryPreprocessor = preprocessor;
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
