#include "PkbAbstractor.h"
#include "PatternAbstractorHelper.h"

list<pair<StmtNum, VarName>> pql::PatternAbstractorHelper::getAssignPatternAllStmtsSubMatch(const Value& value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    ListOfStmtNos listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
    ListOfStmtNos::iterator itAssign;

    if (value.empty() || value == "_") {
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            if (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    } else {
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());

            if (value == varName && (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard)) {
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PatternAbstractorHelper::getAssignPatternAllStmtsFullMatch(const Value& value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    ListOfStmtNos listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
    ListOfStmtNos::iterator itAssign;

    if (value.empty() || value == "_") {
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            if (AssignPostFixTable::isFullExpression(*itAssign, postFixExpression) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    } else {
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());

            if (value == varName && (AssignPostFixTable::isFullExpression(*itAssign, postFixExpression) || postFixStrIsWildcard)) {
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PatternAbstractorHelper::getAssignPatternSpecificStmtSubMatch(StmtNum assignStmtNum, const Value& value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (value.empty() || value == "_") {
        if (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard) {
            VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
            result.push_back(make_pair(assignStmtNum, varName));
        }
    } else {
        VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());

        if (value == varName && (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard)) {
            result.push_back(make_pair(assignStmtNum, varName));
        }
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PatternAbstractorHelper::getAssignPatternSpecificStmtFullMatch(StmtNum assignStmtNum, const Value& value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (value.empty() || value == "_") {
        if (AssignPostFixTable::isFullExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard) {
            VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
            result.push_back(make_pair(assignStmtNum, varName));
        }
    } else {
        VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());

        if (value == varName && (AssignPostFixTable::isFullExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard)) {
            result.push_back(make_pair(assignStmtNum, varName));
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PatternAbstractorHelper::getWhilePatternAllStmts(const Value& value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    ListOfStmtNos listOfWhileStmt = TypeToStmtNumTable::getStmtWithType(pql::DesignEntity::WHILE);
    ListOfStmtNos::iterator itWhile;

    if (value.empty()) {
        for (itWhile = listOfWhileStmt.begin(); itWhile != listOfWhileStmt.end(); ++itWhile) {
            unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(*itWhile);
            if (!listOfWhileControlVars.empty()) {
                result.push_back(make_pair(*itWhile, listOfWhileControlVars));
            }
        }

    } else if (value == "_") {
        for (itWhile = listOfWhileStmt.begin(); itWhile != listOfWhileStmt.end(); ++itWhile) {
            unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(*itWhile);
            result.push_back(make_pair(*itWhile, listOfWhileControlVars));
        }
    } else {
        for (itWhile = listOfWhileStmt.begin(); itWhile != listOfWhileStmt.end(); ++itWhile) {
            unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(*itWhile);
            if (find(begin(listOfWhileControlVars), end(listOfWhileControlVars), value) != end(listOfWhileControlVars)) {
                // contains value
                result.push_back(make_pair(*itWhile, listOfWhileControlVars));
            }
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PatternAbstractorHelper::getIfPatternAllStmts(const Value &value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    ListOfStmtNos listOfIfStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
    ListOfStmtNos::iterator itIf;

    if (value.empty()) {
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            if (!listOfIfControlVars.empty()) {
                result.push_back(make_pair(*itIf, listOfIfControlVars));
            }
        }

    } else if (value == "_") {
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            result.push_back(make_pair(*itIf, listOfIfControlVars));
        }
    } else {
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            if (find(begin(listOfIfControlVars), end(listOfIfControlVars), value) != end(listOfIfControlVars)) {
                result.push_back(make_pair(*itIf, listOfIfControlVars));
            }
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PatternAbstractorHelper::getWhilePatternSpecificStmt(StmtNum whileStmtNum, const Value& value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    if (value.empty()) {
        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        if (!listOfWhileControlVars.empty()) {
            result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
        }
    } else if (value == "_") {
        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
    } else {
        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        if (find(begin(listOfWhileControlVars), end(listOfWhileControlVars), value) != end(listOfWhileControlVars)) {
            result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PatternAbstractorHelper::getIfPatternSpecificStmt(StmtNum ifStmtNum, const Value& value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    if (value.empty()) {
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        if (!listOfIfControlVars.empty()) {
            result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
        }
    } else if (value == "_") {
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
    } else {
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        if (find(begin(listOfIfControlVars), end(listOfIfControlVars), value) != end(listOfIfControlVars)) {
            result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
        }
    }
    return result;
}