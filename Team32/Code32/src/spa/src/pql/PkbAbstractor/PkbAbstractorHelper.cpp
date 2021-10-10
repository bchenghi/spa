#include "PkbAbstractorHelper.h"
#include "PkbAbstractor.h"
#include <algorithm>

bool pql::PkbAbstractorHelper::isNum(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesProcNameHelper(const string& procName, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    if (varName.empty() || varName == "_") {
        // Case: uses(procName, v), uses(procName, _)
        unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(procName);
        if (!listOfVarsUsed.empty()) {
            result.push_back(make_pair(procName, listOfVarsUsed));
        }
    } else {
        // Case: uses(procName, varName)
        unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(procName);

        if (listOfVarsUsed.find(varName) != listOfVarsUsed.end()) {
            // varName is in var used list
            unordered_set<VarName> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesProcNameHelper(const string& procName, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    if (varName.empty() || varName == "_") {
        // Case: modifies(procName, v), modifies(procName, _)
        unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (!listOfVarsModified.empty()) {
            result.push_back(make_pair(procName, listOfVarsModified));
        }
    } else {
        // Case: modifies(procName, varName)
        unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
            // varName is in var modifies list
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesStmtNumHelper(StmtNum stmtNum, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName.empty() || varName == "_") {
        // Case: uses(2, v), uses(2, _)
        unordered_set<VarName> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);

        if (!listOfVarsStmtUses.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtUses));
        }
    } else {
        // Case: uses(2, "count")
        unordered_set<VarName> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);
        if (find(begin(listOfVarsStmtUses), end(listOfVarsStmtUses), varName) != end(listOfVarsStmtUses)) {
            // "count" is in var used list
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesStmtNumHelper(StmtNum stmtNum, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName.empty() || varName == "_") {
        // Case: modifies(2, v), modifies(2, _)
        unordered_set<VarName> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);

        if (!listOfVarsStmtModifies.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtModifies));
        }
    } else {
        // Case: modifies(2, "count")
        unordered_set<VarName> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);
        if (find(begin(listOfVarsStmtModifies), end(listOfVarsStmtModifies), varName) != end(listOfVarsStmtModifies)) {
            // "count" is in var modifies list
            unordered_set<VarName> varNameUsed = {varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}


list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesDesignEntityHelper(DesignEntity designEntity, const VarName& varName) {
    // LHS is Design entity
    list<pair<string, unordered_set<VarName>>> result;

    switch(designEntity) {
        case DesignEntity::ASSIGN:
            result = usesAssignHelper(varName);
            break;

        case DesignEntity::STMT:
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
        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesDesignEntityHelper(DesignEntity designEntity, const VarName& varName) {
    // LHS is Design entity
    list<pair<string, unordered_set<VarName>>> result;

    switch(designEntity) {
        case DesignEntity::ASSIGN:
            result = modifiesAssignHelper(varName);
            break;

        case DesignEntity::STMT:
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
        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesAssignHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(a, v), uses(a, _)
        // iterate thru all assign stmts, get their variables
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itAssign);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var used
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itAssign);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesAssignHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(a, v), modifies(a, _)
        // iterate thru all assign stmts, get their variables
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itAssign);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var modified
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itAssign);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesStmtHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName.empty() || varName == "_") {
        // Case: uses(s, v), uses(s, _)
        // iterate thru all stmts, get their variables
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(i);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(s, "count")
        // iterate thru all stmts, get their variables, check if "count" is inside

        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(i);
            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(i);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesStmtHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName.empty() || varName == "_") {
        // Case: modifies(s, v), modifies(s, _)
        // iterate thru all stmts, get their variables
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(i);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(s, "count")
        // iterate thru all stmts, get their variables, check if "count" is inside
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(i);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(i);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesPrintHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(pn, v), uses(pn, _)
        // iterate thru all print stmts, get their variables
        ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
        ListOfStmtNos::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itPrint);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itPrint);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(pn, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
        ListOfStmtNos::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt, get the list of var used
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itPrint);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itPrint);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesReadHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(r, v), modifies(r, _)
        // iterate thru all read stmts, get their variables
        ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
        ListOfStmtNos::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itRead);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itRead);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(pn, "count")
        // iterate thru all read stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
        ListOfStmtNos::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt, get the list of var modified
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itRead);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itRead);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesWhileHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(w, v), uses(w, _)
        // iterate thru all while stmts, get their variables
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itWhile);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(w, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var used
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itWhile);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesWhileHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(w, v), modifies(w, _)
        // iterate thru all while stmts, get their variables
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            unordered_set<VarName> listOfVarModifies = ModifyTable::getStmtModify(*itWhile);
            if (!listOfVarModifies.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarModifies));
            }
        }
    } else {
        // Case: modifies(w, "count")
        // iterate thru all while stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
        ListOfStmtNos::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var modified
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itWhile);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesIfHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(if, v), uses(w, _)
        // iterate thru all if stmts, get their variables
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itIf);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            unordered_set<VarName> listOfVarUsed = UseTable::getStmtUse(*itIf);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesIfHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(if, v), modifies(w, _)
        // iterate thru all if stmts, get their variables
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itIf);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        ListOfStmtNos listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
        ListOfStmtNos::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            unordered_set<VarName> listOfVarModified = ModifyTable::getStmtModify(*itIf);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesProcHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(p, v), uses(p, _)
        // iterate thru all procedures, get their variables

        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (!listOfVarsUsed.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsUsed));
            }
        }
    } else {
        // Case: uses(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
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

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesProcHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(p, v), modifies(p, _)
        // iterate thru all procedures, get their variables

        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VarName> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (!listOfVarsModified.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsModified));
            }
        }
    } else {
        // Case: modifies(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
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

list<pair<StmtNum, VarName>> pql::PkbAbstractorHelper::getAssignPatternAllStmts(const Value& value, PostFixExpression postFixExpression, bool hasUnderscores) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    ListOfStmtNos listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
    ListOfStmtNos::iterator itAssign;

    if (value.empty() || value == "_") {
        // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            // check if rhs contains postFixStr
            if (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    } else {
        // case: a("count", "count + 1"), a("count", _)
        // check if lhs and rhs match
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
            if (value == varName && (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard)) {
                result.push_back(make_pair(*itAssign, varName));
            }
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PkbAbstractorHelper::getWhilePatternAllStmts(const Value& value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    ListOfStmtNos listOfWhileStmt = TypeToStmtNumTable::getStmtWithType(pql::DesignEntity::WHILE);
    ListOfStmtNos::iterator itWhile;

    if (value.empty()) {
        //  while(v, _), only while stmts with control vars

        for (itWhile = listOfWhileStmt.begin(); itWhile != listOfWhileStmt.end(); ++itWhile) {
            unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(*itWhile);
            if (!listOfWhileControlVars.empty()) {
                result.push_back(make_pair(*itWhile, listOfWhileControlVars));
            }
        }

    } else if (value == "_") {
        // while(_, _), any while stmts

        for (itWhile = listOfWhileStmt.begin(); itWhile != listOfWhileStmt.end(); ++itWhile) {
            unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(*itWhile);
            result.push_back(make_pair(*itWhile, listOfWhileControlVars));
        }
    } else {
        //  Pattern while (“x”, _)
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

list<pair<StmtNum, unordered_set<VarName>>> pql::PkbAbstractorHelper::getIfPatternAllStmts(const Value &value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    ListOfStmtNos listOfIfStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
    ListOfStmtNos::iterator itIf;

    if (value.empty()) {
        //  if(v, _),   only if stmts with control vars
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            if (!listOfIfControlVars.empty()) {
                result.push_back(make_pair(*itIf, listOfIfControlVars));
            }
        }

    } else if (value == "_") {
        // if(_, _),   any if stmts
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            result.push_back(make_pair(*itIf, listOfIfControlVars));
        }
    } else {
        //  Pattern if(“x”, _)
        for (itIf = listOfIfStmt.begin(); itIf != listOfIfStmt.end(); ++itIf) {
            unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(*itIf);
            if (find(begin(listOfIfControlVars), end(listOfIfControlVars), value) != end(listOfIfControlVars)) {
                result.push_back(make_pair(*itIf, listOfIfControlVars));
            }
        }
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PkbAbstractorHelper::getAssignPatternSpecificStmt(StmtNum assignStmtNum, const Value& value, PostFixExpression postFixExpression, bool hasUnderscores) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (value.empty() || value == "_") {
        // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
        if (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard) {
            VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
            result.push_back(make_pair(assignStmtNum, varName));
        }
    } else {
        // case: a("count", "count + 1"), a("count", _)
        VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
        if (value == varName && (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard)) {
            result.push_back(make_pair(assignStmtNum, varName));
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PkbAbstractorHelper::getWhilePatternSpecificStmt(StmtNum whileStmtNum, const Value& value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    if (value.empty()) {
        //  while(v, _),   only while stmts w control vars
        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        if (!listOfWhileControlVars.empty()) {
            result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
        }
    } else if (value == "_") {
        // while(_, _),   any while stmts

        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
    } else {
        //  Pattern while (“x”, _)
        unordered_set<VarName> listOfWhileControlVars = WhileControlTable::getWhileControlVars(whileStmtNum);
        if (find(begin(listOfWhileControlVars), end(listOfWhileControlVars), value) != end(listOfWhileControlVars)) {
            result.push_back(make_pair(whileStmtNum, listOfWhileControlVars));
        }
    }
    return result;
}

list<pair<StmtNum, unordered_set<VarName>>> pql::PkbAbstractorHelper::getIfPatternSpecificStmt(StmtNum ifStmtNum, const Value &value) {
    list<pair<StmtNum, unordered_set<VarName>>> result;

    if (value.empty()) {
        //  if(v, _)   only if stmts w control vars
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        if (!listOfIfControlVars.empty()) {
            result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
        }
    } else if (value == "_") {
        // if(_, _)   any if stmts
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
    } else {
        //  Pattern if(“x”, _)
        unordered_set<VarName> listOfIfControlVars = IfControlTable::getIfControlVars(ifStmtNum);
        if (find(begin(listOfIfControlVars), end(listOfIfControlVars), value) != end(listOfIfControlVars)) {
            result.push_back(make_pair(ifStmtNum, listOfIfControlVars));
        }
    }
    return result;
}