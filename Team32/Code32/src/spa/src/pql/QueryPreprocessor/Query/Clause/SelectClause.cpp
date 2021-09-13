#include "SelectClause.h"

using std::pair;
using std::vector;
using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;

// Returns all combinations of values of the entities in the select clauses
vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinations(PkbAbstractor *pkbAbstractor) {
    LIST_OF_STMT_NO listOfStmtNo = {};
    switch(queryDesignEntity.designEntity) {
        case DesignEntity::Assign: {
            listOfStmtNo = pkbAbstractor->getAllAssignStmts();
            break;
        }
        case DesignEntity::Call: {
            listOfStmtNo = pkbAbstractor->getAllCallStmts();
            break;
        }
        case DesignEntity::Constant: {
            vector<std::string> constants = pkbAbstractor->getAllConstants();
            return getAllEntityCombinationsFromValues(constants);
        }
        case DesignEntity::If: {
            listOfStmtNo = pkbAbstractor->getAllIfStmts();
            break;
        }
        case DesignEntity::Print: {
            listOfStmtNo = pkbAbstractor->getAllPrintStmts();
            break;
        }
        case DesignEntity::Procedure: {
            LIST_OF_PROC_NAME procNames = pkbAbstractor->getAllProcNames();
            return getAllEntityCombinationsFromValues(procNames);
        }
        case DesignEntity::Read: {
            listOfStmtNo = pkbAbstractor->getAllReadStmts();
            break;
        }
        case DesignEntity::Stmt: {
            int largestStmtNum = pkbAbstractor->getLargestStmtNum();
            return getAllEntityCombinationsFromLargestInt(largestStmtNum);
        }
        case DesignEntity::Variable: {
            LIST_OF_VAR_NAME varNamesSet = pkbAbstractor->getAllVarNames();
            vector<std::string> varNames = vector(varNamesSet.begin(), varNamesSet.end());
            return getAllEntityCombinationsFromValues(varNames);
        }
        case DesignEntity::While: {
            listOfStmtNo = pkbAbstractor->getAllWhileStmts();
            break;
        }
    }

    return getAllEntityCombinationsFromStmtLst(listOfStmtNo);
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinationsFromStmtLst(LIST_OF_STMT_NO listOfStmtNo) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (int stmtNum: listOfStmtNo) {
        vector<pair<QueryDesignEntity, QueryArgValue>> current = {};
        QueryArgValue argValue(DesignEntity::Stmt, std::to_string(stmtNum));
        pair<QueryDesignEntity, QueryArgValue> designEntityValuePair = pair(queryDesignEntity, argValue);
        current.push_back(designEntityValuePair);
        result.push_back(current);
    }
    return result;
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinationsFromValues(vector<std::string> listOfValues) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (std::string value: listOfValues) {
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
        QueryArgValue argValue(DesignEntity::Stmt, std::to_string(i));
        pair<QueryDesignEntity, QueryArgValue> designEntityValuePair = pair(queryDesignEntity, argValue);
        current.push_back(designEntityValuePair);
        result.push_back(current);
    }
    return result;
}

bool SelectClause::operator==(const SelectClause& other) const {
    return queryDesignEntity == other.queryDesignEntity;
};
