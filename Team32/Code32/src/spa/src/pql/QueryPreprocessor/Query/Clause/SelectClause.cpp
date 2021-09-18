#include "SelectClause.h"

using std::pair;
using std::vector;
using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;

// Returns all combinations of values of the entities in the select clauses
vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinations(PkbAbstractor *pkbAbstractor) {
    ListOfStmtNos listOfStmtNo = {};
    switch(queryDesignEntity.designEntity) {
        case DesignEntity::ASSIGN: {
            listOfStmtNo = pkbAbstractor->getAllAssignStmts();
            break;
        }
        case DesignEntity::CALL: {
            listOfStmtNo = pkbAbstractor->getAllCallStmts();
            break;
        }
        case DesignEntity::CONSTANT: {
            vector<std::string> constants = pkbAbstractor->getAllConstants();
            return getAllEntityCombinationsFromValues(constants);
        }
        case DesignEntity::IF: {
            listOfStmtNo = pkbAbstractor->getAllIfStmts();
            break;
        }
        case DesignEntity::PRINT: {
            listOfStmtNo = pkbAbstractor->getAllPrintStmts();
            break;
        }
        case DesignEntity::PROCEDURE: {
            ListOfProcNames procNames = pkbAbstractor->getAllProcNames();
            return getAllEntityCombinationsFromValues(procNames);
        }
        case DesignEntity::READ: {
            listOfStmtNo = pkbAbstractor->getAllReadStmts();
            break;
        }
        case DesignEntity::STMT: {
            int largestStmtNum = pkbAbstractor->getLargestStmtNum();
            return getAllEntityCombinationsFromLargestInt(largestStmtNum);
        }
        case DesignEntity::VARIABLE: {
            ListOfVarNames varNamesSet = pkbAbstractor->getAllVarNames();
            vector<std::string> varNames = vector(varNamesSet.begin(), varNamesSet.end());
            return getAllEntityCombinationsFromValues(varNames);
        }
        case DesignEntity::WHILE: {
            listOfStmtNo = pkbAbstractor->getAllWhileStmts();
            break;
        }
    }

    return getAllEntityCombinationsFromStmtLst(listOfStmtNo);
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinationsFromStmtLst(const ListOfStmtNos& listOfStmtNo) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (int stmtNum: listOfStmtNo) {
        vector<pair<QueryDesignEntity, QueryArgValue>> current = {};
        QueryArgValue argValue(DesignEntity::STMT, std::to_string(stmtNum));
        pair<QueryDesignEntity, QueryArgValue> designEntityValuePair = pair(queryDesignEntity, argValue);
        current.push_back(designEntityValuePair);
        result.push_back(current);
    }
    return result;
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinationsFromValues(const vector<std::string>& listOfValues) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (const std::string& value: listOfValues) {
        vector<pair<QueryDesignEntity, QueryArgValue>> current = {};
        QueryArgValue argValue(queryDesignEntity.designEntity, value);
        pair<QueryDesignEntity, QueryArgValue> designEntityValuePair = pair(queryDesignEntity, argValue);
        current.push_back(designEntityValuePair);
        result.push_back(current);
    }
    return result;
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinationsFromLargestInt(int largestStmtNum) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (int i = 1; i <= largestStmtNum; i++) {
        vector<pair<QueryDesignEntity, QueryArgValue>> current = {};
        QueryArgValue argValue(DesignEntity::STMT, std::to_string(i));
        pair<QueryDesignEntity, QueryArgValue> designEntityValuePair = pair(queryDesignEntity, argValue);
        current.push_back(designEntityValuePair);
        result.push_back(current);
    }
    return result;
}

bool SelectClause::operator==(const SelectClause& other) const {
    return queryDesignEntity == other.queryDesignEntity;
};
