#include "PkbAbstractorHelper.h"
#include "PkbAbstractor.h"
#include <algorithm>

using std::unordered_map;

unordered_map<Value, Graph> pql::PkbAbstractorHelper::graphsMap;

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
                unordered_set<VarName> varNameUsed = { varName };
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
                string stmtNumStr = std::to_string(*itIf);
                result.push_back(make_pair(stmtNumStr, listOfVarModified));
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
                string stmtNumStr = std::to_string(*itIf);
                unordered_set<VarName> varNameUsed = {varName };
                result.push_back(make_pair(stmtNumStr, varNameUsed));
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

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::usesCallHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: uses(c, v), uses(c, _)
        // iterate thru all procedures, get their variables, get call stmts of the proc

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
        // Case: uses(c, "count")
        // iterate thru all proc, get their variables, check if "count" is inside, get call stmts of proc
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

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractorHelper::modifiesCallHelper(const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (varName.empty() || varName == "_") {
        // Case: modifies(c, v), modifies(c, _)
        // iterate thru all procedures, get their variables, get the call stmt nums of the procedures

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
        // Case: modifies(c, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
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

list<pair<StmtNum, VarName>> pql::PkbAbstractorHelper::getAssignPatternAllStmts(const Value& value, PostFixExpression postFixExpression, bool hasUnderscores) {
    list<pair<StmtNum, VarName>> result;
    bool postFixStrIsWildcard = postFixExpression.empty();
    bool isPatternFullMatch = !hasUnderscores;

    ListOfStmtNos listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
    ListOfStmtNos::iterator itAssign;

    if (value.empty() || value == "_") {
        // case: a(v, _"count + 1"_), a("_", "count + 1"), a(v, _)
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            if (isPatternFullMatch) {
                // check if rhs contains postFixStr full match

                if (AssignPostFixTable::isFullExpression(*itAssign, postFixExpression) || postFixStrIsWildcard) {
                    VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
                    result.push_back(make_pair(*itAssign, varName));
                }
            } else {
                // check if rhs contains postFixStr subexpression

                if (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard) {
                    VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());
                    result.push_back(make_pair(*itAssign, varName));
                }
            }
        }
    } else {
        // case: a("count", "count + 1"), a("count", _)
        // check if lhs and rhs match
        for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
            VarName varName = *(ModifyTable::getStmtModify(*itAssign).begin());

            if (isPatternFullMatch) {
                if (value == varName && (AssignPostFixTable::isFullExpression(*itAssign, postFixExpression) || postFixStrIsWildcard)) {
                    result.push_back(make_pair(*itAssign, varName));
                }
            } else {
                if (value == varName && (AssignPostFixTable::isSubExpression(*itAssign, postFixExpression) || postFixStrIsWildcard)) {
                    result.push_back(make_pair(*itAssign, varName));
                }
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
    bool isPatternFullMatch = !hasUnderscores;

    if (value.empty() || value == "_") {
        // case: a(v, "count + 1"), a("_", _"count + 1"_), a(v, _)

        if (isPatternFullMatch) {
            if (AssignPostFixTable::isFullExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
                result.push_back(make_pair(assignStmtNum, varName));
            }
        } else {
            if (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
                result.push_back(make_pair(assignStmtNum, varName));
            }
        }
    } else {
        // case: a("count", "count + 1"), a("count", _)
        VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());

        if (isPatternFullMatch) {
            if (value == varName && (AssignPostFixTable::isFullExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard)) {
                result.push_back(make_pair(assignStmtNum, varName));
            }
        } else {
            if (value == varName && (AssignPostFixTable::isSubExpression(assignStmtNum, postFixExpression) || postFixStrIsWildcard)) {
                result.push_back(make_pair(assignStmtNum, varName));
            }
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

list<pair<StmtNum, unordered_set<VarName>>> pql::PkbAbstractorHelper::getIfPatternSpecificStmt(StmtNum ifStmtNum, const Value& value) {
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

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValues(DesignEntity designEntity1, AttributeType attributeType1,
                                                                     DesignEntity designEntity2, AttributeType attributeType2) {

    list<pair<Value, Value>> result;

    switch(designEntity1) {
        case DesignEntity::ASSIGN:
            result = getWithNoneValuesHelperAssign1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::CALL:
            result = getWithNoneValuesHelperCall1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::CONSTANT:
            result = getWithNoneValuesHelperConstant1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::IF:
            result = getWithNoneValuesHelperIf1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PRINT:
            result = getWithNoneValuesHelperPrint1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PROCEDURE:
            result = getWithNoneValuesHelperProcedure1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PROGRAM_LINE:
            result = getWithNoneValuesHelperStmtOrProgline1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::READ:
            result = getWithNoneValuesHelperRead1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::STMT:
            result = getWithNoneValuesHelperStmtOrProgline1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::VARIABLE:
            result = getWithNoneValuesHelperVariable1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::WHILE:
            result = getWithNoneValuesHelperWhile1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::NONE:
            break;

        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperAssign1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::ASSIGN || designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // a.stmt# = a.stmt# / s.stmt# / n
                // return (a.stmt#, a.stmt#)
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                    result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // a.stmt# = constant.value
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    // for all assign stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itAssignStmtNums) != listOfConstants.end()) {
                        string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                        result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperCall1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::PROCEDURE_NAME) {
        if (designEntity2 == DesignEntity::PROCEDURE || designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // c.procName = p.procName / c.procName
                // return list of pair(call stmt num, procName being called)

                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for (itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    string callStmtNumStr = std::to_string(*itCallStmts);
                    ProcName procCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    result.push_back(make_pair(callStmtNumStr, procCalled));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // c.procName = r.varName
                // return (callStmtNum, readStmtNum)
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itRead;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
                        VarName readVarName = *(ModifyTable::getStmtModify(*itRead).begin());

                        if (procNameCalled == readVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string readStmtNumStr = std::to_string(*itRead);
                            result.push_back(make_pair(callStmtNumstr, readStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2  == AttributeType::VARIABLE_NAME) {
                // c.procName = print.varName
                // return (callStmtNum, printStmtNum)
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrint;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrint).begin());

                        if (procNameCalled == printVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string printStmtNumStr = std::to_string(*itPrint);
                            result.push_back(make_pair(callStmtNumstr, printStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // c.procName = v.varName

                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    if (listOfVarNames.find(procNameCalled) != listOfVarNames.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmts);
                        result.push_back(make_pair(callStmtNumStr, procNameCalled));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.stmt# = c.stmt#
                // return (c.stmt#, c.stmt#)
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    string callStmtNumStr = std::to_string(*itCallStmtNums);
                    result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // call.stmt# = constant.value
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    // for all call stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itCallStmtNums) != listOfConstants.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmtNums);
                        result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperConstant1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::VALUE) {
        if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // c.value = c.value
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    string constStr = std::to_string(*itConstants);
                    result.push_back(make_pair(constStr, constStr));
                }
            }
        } else if (designEntity2 == DesignEntity::STMT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = s.stmt#
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::NONE) {
                // c.value = n
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::ASSIGN) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = a.stmt#
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    // for all assign stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itAssignStmtNums) != listOfConstants.end()) {
                        string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                        result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = call.stmt#
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    // for all call stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itCallStmtNums) != listOfConstants.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmtNums);
                        result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::IF) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = if.stmt#
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    // for all if stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itIfStmtNums) != listOfConstants.end()) {
                        string ifStmtNumStr = std::to_string(*itIfStmtNums);
                        result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::WHILE) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = while.stmt#
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    // for all while stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itWhileStmtNums) != listOfConstants.end()) {
                        string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                        result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = print.stmt#
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    // for all print stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itPrintStmtNums) != listOfConstants.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // c.value = read.stmt#
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // for all read stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itReadStmtNums) != listOfConstants.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmtNums);
                        result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperIf1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::IF || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // if.stmt# = if.stmt# / s.stmt3 / n
                // return (if.stmt#, if.stmt#)
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    string ifStmtNumStr = std::to_string(*itIfStmtNums);
                    result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // if.stmt# = constant.value
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    // for all if stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itIfStmtNums) != listOfConstants.end()) {
                        string ifStmtNumStr = std::to_string(*itIfStmtNums);
                        result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperPrint1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PRINT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // p.stmt# = p.stmt# / s.stmt# / n
                // return (p.stmt#, p.stmt#)
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // print.stmt# = constant.value
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    // for all print stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itPrintStmtNums) != listOfConstants.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::PRINT || designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // p.varName = p.varName / v.varName
                // return: (varName, varName)
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    // for each print stmt num, get the var used
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    result.push_back(make_pair(printStmtNumStr, printVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // p.varName = r.varName

                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // get read varName
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());

                    for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                        // for each print stmt num, get the var used
                        VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                        if (readVarName == printVarName) {
                            string readStmtNumStr = std::to_string(*itReadStmtNums);
                            string printStmtNumStr = std::to_string(*itPrintStmtNums);
                            result.push_back(make_pair(printStmtNumStr, readStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // p.varName = proc.procName

                ListOfProcNames listOfProcName = ProcTable::getAllProcedure();

                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    // for each print stmt num, get the var used
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    if (listOfProcName.find(printVarName) !=  listOfProcName.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // p.varName = c.procName
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrint;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrint).begin());

                        if (procNameCalled == printVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string printStmtNumStr = std::to_string(*itPrint);
                            result.push_back(make_pair(printStmtNumStr, callStmtNumstr));
                        }
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperProcedure1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::PROCEDURE_NAME) {
        if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // p.procName = c.procName
                // return list of pair(call stmt num, procName being called)

                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for (itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    string callStmtNumStr = std::to_string(*itCallStmts);
                    ProcName procCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    result.push_back(make_pair(callStmtNumStr, procCalled));
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // p.procName = p.procName
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfProcNames::iterator itProcNames;

                for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
                    result.push_back(make_pair(*itProcNames, *itProcNames));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // p.procName = r.varName
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmts;

                for (itReadStmts = listOfReadStmts.begin(); itReadStmts != listOfReadStmts.end(); ++itReadStmts) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmts).begin());
                    if (listOfProcNames.find(readVarName) != listOfProcNames.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmts);
                        result.push_back(make_pair(readStmtNumStr, readVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // p.procName = print.varName
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmts;

                for (itPrintStmts = listOfPrintStmts.begin(); itPrintStmts != listOfPrintStmts.end(); ++itPrintStmts) {
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmts).begin());
                    if (listOfProcNames.find(printVarName) != listOfProcNames.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmts);
                        result.push_back(make_pair(printStmtNumStr, printVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // p.procName = v.varName
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for (itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    if (listOfProcNames.find(*itVarNames) != listOfProcNames.end()) {
                        result.push_back(make_pair(*itVarNames, *itVarNames));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperStmtOrProgline1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM || attributeType1 == AttributeType::NONE) {
        if (designEntity2 == DesignEntity::IF)  {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // n = if.stmt#
                // return all if stmt nums
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIf;

                for (itIf = listOfIfStmtNums.begin(); itIf != listOfIfStmtNums.end(); ++itIf) {
                    string ifStmtNumStr = std::to_string(*itIf);
                    result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::WHILE) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // n = while.stmt#
                // return all while stmt nums
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhile;

                for (itWhile = listOfWhileStmtNums.begin(); itWhile != listOfWhileStmtNums.end(); ++itWhile) {
                    string whileStmtNumStr = std::to_string(*itWhile);
                    result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // n = s.stmt# / n
                // return all stmt nums
                StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

                for (int i = 1; i <= largestStmtNum; i++) {
                    string stmtNum = std::to_string(i);
                    result.push_back(make_pair(stmtNum, stmtNum));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // n = r.stmt#
                // return (r.stmt#, r.stmt#)
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // n = p.stmt#
                // return (p.stmt#, p.stmt#)
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::ASSIGN) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                // n = a.stmt#
                // return (a.stmt#, a.stmt#)
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                    result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // n = c.value
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperRead1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::READ || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // r.stmt# = r.stmt# / s.stmt# / n
                // return (r.stmt#, r.stmt#)
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // read.stmt# = c.value
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // for all read stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itReadStmtNums) != listOfConstants.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmtNums);
                        result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::READ || designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // r.varName = r.varName / v.varName
                // return: (varName, varName)
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // for each read stmt num, get the var used
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                    result.push_back(make_pair(readStmtNumStr, readVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // r.varName = p.varName
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // get read varName
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());

                    for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                        // for each print stmt num, get the var used
                        VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                        if (readVarName == printVarName) {
                            string readStmtNumStr = std::to_string(*itReadStmtNums);
                            string printStmtNumStr = std::to_string(*itPrintStmtNums);
                            result.push_back(make_pair(readStmtNumStr, printStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // r.varName = proc.procName

                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmts;

                for (itReadStmts = listOfReadStmts.begin(); itReadStmts != listOfReadStmts.end(); ++itReadStmts) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmts).begin());
                    if (listOfProcNames.find(readVarName) != listOfProcNames.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmts);
                        result.push_back(make_pair(readStmtNumStr, readVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // r.varName = c.procName
                // return (readStmtNum, callStmtNum)
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itRead;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
                        VarName readVarName = *(ModifyTable::getStmtModify(*itRead).begin());

                        if (procNameCalled == readVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string readStmtNumStr = std::to_string(*itRead);
                            result.push_back(make_pair(readStmtNumStr, callStmtNumstr));
                        }
                    }

                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperVariable1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // v.varName = p.varName
                // return: (printStmtNum, varName)
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    // for each print stmt num, get the var used
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    result.push_back(make_pair(printStmtNumStr, printVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // v.varName = r.varName
                // return: (readStmtNum, varName)
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    // for each read stmt num, get the var used
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                    result.push_back(make_pair(readStmtNumStr, readVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                // v.varName = v.varName

                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for(itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    result.push_back(make_pair(*itVarNames, *itVarNames));
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // v.varName = p.procName
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for (itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    if (listOfProcNames.find(*itVarNames) != listOfProcNames.end()) {
                        result.push_back(make_pair(*itVarNames, *itVarNames));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                // v.varName = c.procName
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    if (listOfVarNames.find(procNameCalled) != listOfVarNames.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmts);
                        result.push_back(make_pair(callStmtNumStr, procNameCalled));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithNoneValuesHelperWhile1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::WHILE || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                // while.stmt# = while.stmt# / s.stmt3 / n
                // return (while.stmt#, while.stmt#)
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                    result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                // while.stmt# = constant.value
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    // for all while stmt nums, check if it is also a constant
                    if (listOfConstants.find(*itWhileStmtNums) != listOfConstants.end()) {
                        string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                        result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithOneValue(DesignEntity designEntity1, AttributeType attributeType1, const Value& value2) {
    list<pair<Value, Value>> result;

    if (designEntity1 == DesignEntity::ASSIGN) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            // a.stmt# = "3"
            ListOfStmtNos assignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (assignStmtNums.find(numValue2) != assignStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } if (designEntity1 == DesignEntity::CALL) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            // c.procName = "First"
            // return (stmtNum, "First")

            ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(value2);
            ListOfStmtNos::iterator itCalls;

            for (itCalls = callStmtNums.begin(); itCalls != callStmtNums.end(); ++itCalls) {
                string callStmtNumStr = std::to_string(*itCalls);
                result.push_back(make_pair(callStmtNumStr, value2));
            }
        } else if (attributeType1 == AttributeType::STMT_NUM) {
            // c.stmt# = "4"
            ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(value2);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (callStmtNums.find(numValue2) != callStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::CONSTANT) {
        if (attributeType1 == AttributeType::VALUE) {
            // c.value = "4"
            ListOfConstants listOfConstants = ConstantTable::getAllConstant();

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (listOfConstants.find(numValue2) != listOfConstants.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::IF) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            // if.stmt# = "4"

            ListOfStmtNos ifStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (ifStmtNums.find(numValue2) != ifStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::WHILE) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            // while.stmt# = "4"

            ListOfStmtNos whileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (whileStmtNums.find(numValue2) != whileStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PRINT) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            // print.stmt# = "4"
            ListOfStmtNos printStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (printStmtNums.find(numValue2) != printStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            // print.varName = "x"
            // return: (stmtNum, varName)
            ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
            ListOfStmtNos::iterator itPrintStmtNums;

            for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                // for each print stmt num, get the var used
                VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                if (printVarName == value2) {
                    string printStmtStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtStr, printVarName));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::READ) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            // read.stmt# = "4"
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (readStmtNums.find(numValue2) != readStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            // read.varName = "x"
            // return: (stmtNum, varName)
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
            ListOfStmtNos::iterator itReadStmtNums;

            for(itReadStmtNums = readStmtNums.begin(); itReadStmtNums != readStmtNums.end(); ++itReadStmtNums) {
                // for each read stmt num, get the var used, then check if it = value2
                VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                if (readVarName == value2) {
                    string readStmtStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtStr, readVarName));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PROCEDURE) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            // p.procName = "First"

            ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

            if (listOfProcNames.find(value2) != listOfProcNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    } else if (designEntity1 == DesignEntity::PROGRAM_LINE || designEntity1 == DesignEntity::STMT) {
        if (attributeType1 == AttributeType::NONE || attributeType1 == AttributeType::STMT_NUM) {
            // n = "4", s.stmt# = "4"

            if (isNum(value2)) {
                int numValue2 = std::stoi(value2);
                int largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                if (numValue2 <= largestStmtNum) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::VARIABLE) {
        if (attributeType1 == AttributeType::VARIABLE_NAME) {
            // v.varName = "x"
            ListOfVarNames listOfVarNames = VarTable::getAllVarName();

            if (listOfVarNames.find(value2) != listOfVarNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractorHelper::getWithBothValues(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    // "x" = "x"
    if (value1 == value2) {
        result.push_back(make_pair(value1, value2));
    }
    return result;
}

Graph pql::PkbAbstractorHelper::initGraph(int size) {
    Graph graph;
    graph.reserve(size);

    for (int i = 0; i < size; i++) {
        vector<size_t> row;
        row.reserve(size);
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }
        graph.push_back(row);
    }
    return graph;
}

Graph pql::PkbAbstractorHelper::createNextStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    Graph nextStarGraph;
    nextStarGraph = initGraph(int(numV));

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            nextStarGraph[i][j] = NextTable::isNext(i+1, j+1);
        }
    }

    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                nextStarGraph[i][j] = (nextStarGraph[i][j] == 1) ||
                                      ((nextStarGraph[i][k] == 1) && nextStarGraph[k][j] == 1) ? 1 : 0;
            }
        }
    }

    return nextStarGraph;
}

unordered_set<ProcLine> pql::PkbAbstractorHelper::getNextStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> nextStarList;

    if (procLine >= nextStarGraph.size())
        return nextStarList;

    for (int j = 0; j < nextStarGraph[procLine - 1].size(); j++) {
        int to = j + 1;
        if (nextStarGraph[procLine - 1][j] == 1) {
            nextStarList.insert(to);
        }
    }
    return nextStarList;
}

unordered_set<ProcLine> pql::PkbAbstractorHelper::getPrevStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> prevStarList;

    for (int i = 0; i < nextStarGraph[procLine - 1].size(); i++) {
        int to = i + 1;
        if (nextStarGraph[i][procLine - 1] == 1) {
            prevStarList.insert(to);
        }
    }
    return prevStarList;
}

bool pql::PkbAbstractorHelper::isSameProc(StmtNum assignStmtNum1, StmtNum assignStmtNum2) {

    ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
    ListOfProcNames::iterator itProcNames;

    for (itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
        ListOfStmtNos listOfStmtNums = ProcTable::getProcStmtList(*itProcNames);

        if ((listOfStmtNums.find(assignStmtNum1) != listOfStmtNums.end()) && (listOfStmtNums.find(assignStmtNum2) != listOfStmtNums.end())) {
            // both stmt nums in same proc
            return true;
        }
    }
    return false;
}

bool pql::PkbAbstractorHelper::isModifiesUsed(StmtNum assignStmtNum1, StmtNum assignStmtNum2) {
    // a1 modifies a variable v which is used in a2

    VarName varModified = *(ModifyTable::getStmtModify(assignStmtNum1).begin());
    ListOfVarNames varsUsed = UseTable::getStmtUse(assignStmtNum2);

    if (varsUsed.find(varModified) != varsUsed.end()) {
        return true;
    }
    return false;
}

bool pql::PkbAbstractorHelper::isAffectsItself(StmtNum assignStmt, VarName varModified){
    // assign stmts will always have one stmt next
    ListOfProgLines nextList = NextTable::getNext(assignStmt);
    if (nextList.empty()) {
        return false;
    }
    StmtNum nextStmt = *(nextList.begin());

    list<vector<StmtNum>> listOfAllPaths = PkbAbstractorHelper::getAllPaths(nextStmt, assignStmt);
    // if there is a path
    if (!listOfAllPaths.empty()) {
        bool isVarNotModifiedByAPath = PkbAbstractorHelper::isVarNotModifiedByAPath(listOfAllPaths, varModified);

        if (isVarNotModifiedByAPath) {
            return true;
        }
    }
    return false;
}

list<vector<StmtNum>> pql::PkbAbstractorHelper::getAllPaths(StmtNum start, StmtNum end) {
    list<vector<StmtNum>> allPaths;
    vector<StmtNum> currPath;
    vector<size_t> isVisited;
    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

    for (int j = 0; j < largestStmtNum; j++) {
        isVisited.push_back(0);
    }

    getAllPathsHelper(start, end, isVisited, currPath, allPaths);
    return allPaths;
}

void pql::PkbAbstractorHelper::getAllPathsHelper(StmtNum start, StmtNum end, vector<size_t>& isVisited, vector<StmtNum>& currPath, list<vector<StmtNum>>& allPaths) {

    if (isVisited[start - 1] == 1) {
        return;
    }

    isVisited[start - 1] = 1;
    currPath.push_back(start);

    if (start == end) {
        // reached the end
        allPaths.push_back(currPath);
        isVisited[start - 1] = 0;
        currPath.pop_back();
        return;
    }
    ListOfProgLines nextList = NextTable::getNext(start);
    ListOfProgLines::iterator itNextList;

    for (itNextList = nextList.begin(); itNextList != nextList.end(); ++itNextList) {
        getAllPathsHelper(*itNextList, end, isVisited, currPath, allPaths);
    }
    currPath.pop_back();
    isVisited[start - 1] = 0;
}

bool pql::PkbAbstractorHelper::isStmtModifiesVar(StmtNum stmtNum, VarName varName) {

    // stmt should only be assign, read or calls
    DesignEntity typeOfStmt = TypeToStmtNumTable::getTypeOfStmt(stmtNum);

    if (typeOfStmt == DesignEntity::ASSIGN || typeOfStmt == DesignEntity::READ || typeOfStmt == DesignEntity::CALL) {
        ListOfVarNames listOfVarsModified = ModifyTable::getStmtModify(stmtNum);
        if (listOfVarsModified.find(varName) != listOfVarsModified.end()) {
            return true;
        }
    }
    return false;
}

bool pql::PkbAbstractorHelper::isVarNotModifiedByAPath(list<vector<StmtNum>> listOfAllPaths, VarName varName) {

    list<vector<StmtNum>>::iterator itPaths;
    for(itPaths = listOfAllPaths.begin(); itPaths != listOfAllPaths.end(); ++itPaths) {
        // for each path
        vector<StmtNum> path = *itPaths;

        if (path.size() == 2) {
            return true;
        }

        for (int i = 1; i < path.size() - 1; i++) {
            // for each stmt between start and end
            StmtNum stmtNum = path[i];
            bool isStmtModifiesVar = PkbAbstractorHelper::isStmtModifiesVar(stmtNum, varName);  // need account for while and if loops

            if (isStmtModifiesVar) {
                // a stmt modifies var
                break;
            }
            if (i == path.size() - 2) {
                // reached the end of a path without finding a stmt that modifies a var
                return true;
            }
        }
    }
    return false;
}

bool pql::PkbAbstractorHelper::isAffects(StmtNum stmtNum1, StmtNum stmtNum2) {

    DesignEntity typeOfStmt1 = TypeToStmtNumTable::getTypeOfStmt(stmtNum1);
    DesignEntity typeOfStmt2 = TypeToStmtNumTable::getTypeOfStmt(stmtNum2);

    if (typeOfStmt1 == DesignEntity::ASSIGN && typeOfStmt2 == DesignEntity::ASSIGN) {
        bool isSameProc = PkbAbstractorHelper::isSameProc(stmtNum1, stmtNum2);
        ListOfVarNames modifiedVarList = ModifyTable::getStmtModify(stmtNum1);
        if (modifiedVarList.empty()) {
            return false;
        }
        VarName varModifiedByA1 = *(modifiedVarList.begin());

        if (isSameProc) {
            bool isModifiesUsed = PkbAbstractorHelper::isModifiesUsed(stmtNum1, stmtNum2);

            if (isModifiesUsed) {

                if (stmtNum1 == stmtNum2) {
                    // same stmt num
                    bool isAffectsItself = PkbAbstractorHelper::isAffectsItself(stmtNum1, varModifiedByA1);
                    return isAffectsItself;
                }

                list<vector<StmtNum>> listOfAllPaths = PkbAbstractorHelper::getAllPaths(stmtNum1, stmtNum2);
                if (!listOfAllPaths.empty()) {
                    // if there is a path
                    bool isVarNotModifiedByAPath = PkbAbstractorHelper::isVarNotModifiedByAPath(listOfAllPaths, varModifiedByA1);

                    if (isVarNotModifiedByAPath) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Graph pql::PkbAbstractorHelper::createAffectsStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    Graph affectsStarGraph;
    affectsStarGraph = initGraph(int(numV));

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            affectsStarGraph[i][j] = PkbAbstractorHelper::isAffects(i + 1, j + 1);
        }
    }

    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                affectsStarGraph[i][j] = (affectsStarGraph[i][j] == 1) ||
                                         ((affectsStarGraph[i][k] == 1) && affectsStarGraph[k][j] == 1) ? 1 : 0;
            }
        }
    }
    return affectsStarGraph;
}

unordered_set<StmtNum> pql::PkbAbstractorHelper::getAffectsStar(StmtNum assignStmt1, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectsStarList;

    if (assignStmt1 >= affectsStarGraph.size())
        return affectsStarList;

    for (int j = 0; j < affectsStarGraph[assignStmt1 - 1].size(); j++) {
        int to = j + 1;
        if (affectsStarGraph[assignStmt1 - 1][j] == 1) {
            affectsStarList.insert(to);
        }
    }
    return affectsStarList;
}

unordered_set<StmtNum> pql::PkbAbstractorHelper::getAffectedByStar(StmtNum assignStmt2, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectedByList;

    for (int i = 0; i < affectsStarGraph[assignStmt2 - 1].size(); i++) {
        int to = i + 1;
        if (affectsStarGraph[i][assignStmt2 - 1] == 1) {
            affectedByList.insert(to);
        }
    }
    return affectedByList;
}

Graph pql::PkbAbstractorHelper::getGraph(Value graphName) {
    auto res = PkbAbstractorHelper::graphsMap.find(graphName);
    if (res != PkbAbstractorHelper::graphsMap.end()) {
        return res->second;
    }
    else {
        return Graph();
    }
}

void pql::PkbAbstractorHelper::addGraph(Value graphName, Graph graph) {
    auto res = PkbAbstractorHelper::graphsMap.find(graphName);
    if (res == PkbAbstractorHelper::graphsMap.end()) {
        PkbAbstractorHelper::graphsMap[graphName] = graph;
    }
}

void pql::PkbAbstractorHelper::clearGraphs() {
    PkbAbstractorHelper::graphsMap.clear();
}