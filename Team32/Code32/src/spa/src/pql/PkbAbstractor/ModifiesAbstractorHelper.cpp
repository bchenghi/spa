#include "PkbAbstractor.h"
#include "ModifiesAbstractorHelper.h"

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesProcNameHelper(const string& procName, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    if (varName.empty() || varName == "_") {
        unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (!listOfVarsModified.empty()) {
            result.push_back(make_pair(procName, listOfVarsModified));
        }
    } else {
        unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesStmtNumHelper(StmtNum stmtNum, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName.empty() || varName == "_") {
        unordered_set<VarName> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);

        if (!listOfVarsStmtModifies.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtModifies));
        }
    } else {
        unordered_set<VarName> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);
        if (find(begin(listOfVarsStmtModifies), end(listOfVarsStmtModifies), varName) != end(listOfVarsStmtModifies)) {
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesDesignEntityHelper(DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    switch(designEntity) {
        case DesignEntity::ASSIGN:
            result = modifiesAssignHelper(varName);
            break;

        case DesignEntity::STMT:
            result = modifiesStmtHelper(varName);
            break;

        case DesignEntity::PROGRAM_LINE:
            result = modifiesStmtHelper(varName);
            break;

        case DesignEntity::READ:
            result = modifiesReadHelper(varName);
            break;

        case DesignEntity::WHILE:
            result = modifiesWhileHelper(varName);
            break;

        case DesignEntity::IF:
            result = modifiesIfHelper(varName);
            break;

        case DesignEntity::PROCEDURE:
            result = modifiesProcHelper(varName);
            break;

        case DesignEntity::CALL:
            result = modifiesCallHelper(varName);
            break;

        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesAssignHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itAssign);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itAssign);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesStmtHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName.empty() || varName == "_") {
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(i);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(i);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                string stmtNum = std::to_string(i);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesReadHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
        ListOfStmtNos::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itRead);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itRead);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
        ListOfStmtNos::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itRead);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                string stmtNum = std::to_string(*itRead);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesWhileHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            unordered_set<VarName> listOfVarModifies = ModifyTable::getStmtModify(*itWhile);
            if (!listOfVarModifies.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarModifies));
            }
        }
    } else {
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itWhile);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesIfHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itIf);
            if (!listOfVarModified.empty()) {
                string stmtNumStr = std::to_string(*itIf);
                result.push_back(make_pair(stmtNumStr, listOfVarModified));
            }
        }
    } else {
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itIf);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                string stmtNumStr = std::to_string(*itIf);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNumStr, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesProcHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (!listOfVarsModified.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsModified));
            }
        }
    } else {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::ModifiesAbstractorHelper::modifiesCallHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (!listOfVarsModified.empty()) {
                ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(*itProc);
                ListOfStmtNos::iterator itCall;

                for (itCall = callStmtNums.begin(); itCall != callStmtNums.end(); ++itCall) {
                    string callStmtStr = std::to_string(*itCall);
                    result.push_back(make_pair(callStmtStr, listOfVarsModified));
                }
            }
        }
    } else {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
                unordered_set<VarName> varNameUsed = { varName };

                ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(*itProc);
                ListOfStmtNos::iterator itCall;

                for (itCall = callStmtNums.begin(); itCall != callStmtNums.end(); ++itCall) {
                    string callStmtStr = std::to_string(*itCall);
                    result.push_back(make_pair(callStmtStr, varNameUsed));
                }
            }
        }
    }
    return result;
}