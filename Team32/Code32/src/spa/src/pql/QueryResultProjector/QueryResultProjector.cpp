#include "QueryResultProjector.h"
#include <iostream>

using pql::QueryResult;
using pql::QueryResultProjector;
using std::cout;

set<string> QueryResultProjector::createResultSet(QueryResult queryResult) {
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
}
