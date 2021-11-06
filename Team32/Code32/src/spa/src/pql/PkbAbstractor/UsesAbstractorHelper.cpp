#include "PkbAbstractor.h"
#include "UsesAbstractorHelper.h"

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesProcNameHelper(const string& procName, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    if (varName.empty() || varName == "_") {
        unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(procName);
        if (!listOfVarsUsed.empty()) {
            result.push_back(make_pair(procName, listOfVarsUsed));
        }
    } else {
        unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(procName);

        if (listOfVarsUsed.find(varName) != listOfVarsUsed.end()) {
            unordered_set<VarName> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesStmtNumHelper(StmtNum stmtNum, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName.empty() || varName == "_") {
        unordered_set<VarName> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);

        if (!listOfVarsStmtUses.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtUses));
        }
    } else {
        unordered_set<VarName> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);
        if (find(begin(listOfVarsStmtUses), end(listOfVarsStmtUses), varName) != end(listOfVarsStmtUses)) {
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesDesignEntityHelper(DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    switch(designEntity) {
        case DesignEntity::ASSIGN:
            result = usesAssignHelper(varName);
            break;

        case DesignEntity::STMT:
            result = usesStmtHelper(varName);
            break;

        case DesignEntity::PROGRAM_LINE:
            result = usesStmtHelper(varName);
            break;

        case DesignEntity::PRINT:
            result = usesPrintHelper(varName);
            break;

        case DesignEntity::WHILE:
            result = usesWhileHelper(varName);
            break;

        case DesignEntity::IF:
            result = usesIfHelper(varName);
            break;

        case DesignEntity::PROCEDURE:
            result = usesProcHelper(varName);
            break;

        case DesignEntity::CALL:
            result = usesCallHelper(varName);
            break;

        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesAssignHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itAssign);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itAssign);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesStmtHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName.empty() || varName == "_") {
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(i);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(i);
            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                string stmtNum = std::to_string(i);
                unordered_set<VarName> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesPrintHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
        ListOfStmtNos::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itPrint);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itPrint);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
        ListOfStmtNos::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itPrint);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                string stmtNum = std::to_string(*itPrint);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesWhileHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itWhile);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itWhile);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesIfHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itIf);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itIf);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                string stmtNum = std::to_string(*itIf);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesProcHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (!listOfVarsUsed.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsUsed));
            }
        }
    } else {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (find(begin(listOfVarsUsed), end(listOfVarsUsed), varName) != end(listOfVarsUsed)) {
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::UsesAbstractorHelper::usesCallHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (!listOfVarsUsed.empty()) {
                ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(*itProc);
                ListOfStmtNos::iterator itCall;

                for (itCall = callStmtNums.begin(); itCall != callStmtNums.end(); ++itCall) {
                    string callStmtStr = std::to_string(*itCall);
                    result.push_back(make_pair(callStmtStr, listOfVarsUsed));
                }
            }
        }
    } else {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (find(begin(listOfVarsUsed), end(listOfVarsUsed), varName) != end(listOfVarsUsed)) {
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