#include "PkbAbstractorHelper.h"
#include "PkbAbstractor.h"
#include <algorithm>

bool pql::PkbAbstractorHelper::isNum(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesProcNameHelper(string procName, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    if (varName == "" || varName == "_") {
        // Case: uses(procName, v), uses(procName, _)
        unordered_set<VAR_NAME> listOfVarsUsed = UseTable::getProcUse(procName);
        if (!listOfVarsUsed.empty()) {
            result.push_back(make_pair(procName, listOfVarsUsed));
        }
    } else {
        // Case: uses(procName, varName)
        unordered_set<VAR_NAME> listOfVarsUsed = UseTable::getProcUse(procName);

        if (listOfVarsUsed.find(varName) != listOfVarsUsed.end()) {
            // varName is in var used list
            unordered_set<VAR_NAME> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesProcNameHelper(string procName, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    if (varName == "" || varName == "_") {
        // Case: modifies(procName, v), modifies(procName, _)
        unordered_set<VAR_NAME> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (!listOfVarsModified.empty()) {
            result.push_back(make_pair(procName, listOfVarsModified));
        }
    } else {
        // Case: modifies(procName, varName)
        unordered_set<VAR_NAME> listOfVarsModified = ModifyTable::getProcModify(procName);
        if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
            // varName is in var modifies list
            unordered_set<VAR_NAME> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesStmtNumHelper(StmtNum stmtNum, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName == "" || varName == "_") {
        // Case: uses(2, v), uses(2, _)
        unordered_set<VAR_NAME> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);

        if (!listOfVarsStmtUses.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtUses));
        }
    } else {
        // Case: uses(2, "count")
        unordered_set<VAR_NAME> listOfVarsStmtUses = UseTable::getStmtUse(stmtNum);
        if (find(begin(listOfVarsStmtUses), end(listOfVarsStmtUses), varName) != end(listOfVarsStmtUses)) {
            // "count" is in var used list
            unordered_set<VAR_NAME> varNameUsed = { varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesStmtNumHelper(StmtNum stmtNum, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName == "" || varName == "_") {
        // Case: modifies(2, v), modifies(2, _)
        unordered_set<VAR_NAME> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);

        if (!listOfVarsStmtModifies.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtModifies));
        }
    } else {
        // Case: modifies(2, "count")
        unordered_set<VAR_NAME> listOfVarsStmtModifies = ModifyTable::getStmtModify(stmtNum);
        if (find(begin(listOfVarsStmtModifies), end(listOfVarsStmtModifies), varName) != end(listOfVarsStmtModifies)) {
            // "count" is in var modifies list
            unordered_set<VAR_NAME> varNameUsed = { varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}


list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesDesignEntityHelper(DesignEntity designEntity, VarName varName) {
    // LHS is Design entity
    list<pair<string, unordered_set<VAR_NAME>>> result;

    switch(designEntity) {
        case DesignEntity::Assign:
            result = usesAssignHelper(varName);
            break;

        case DesignEntity::Stmt:
            result = usesStmtHelper(varName);
            break;

        case DesignEntity::Print:
            result = usesPrintHelper(varName);
            break;

        case DesignEntity::While:
            result = usesWhileHelper(varName);
            break;

        case DesignEntity::If:
            result = usesIfHelper(varName);
            break;

        case DesignEntity::Procedure:
            result = usesProcHelper(varName);
            break;
        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesDesignEntityHelper(DesignEntity designEntity, VarName varName) {
    // LHS is Design entity
    list<pair<string, unordered_set<VAR_NAME>>> result;

    switch(designEntity) {
        case DesignEntity::Assign:
            result = modifiesAssignHelper(varName);
            break;

        case DesignEntity::Stmt:
            result = modifiesStmtHelper(varName);
            break;

        case DesignEntity::Read:
            result = modifiesReadHelper(varName);
            break;

        case DesignEntity::While:
            result = modifiesWhileHelper(varName);
            break;

        case DesignEntity::If:
            result = modifiesIfHelper(varName);
            break;

        case DesignEntity::Procedure:
            result = modifiesProcHelper(varName);
            break;
        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesAssignHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(a, v), uses(a, _)
        // iterate thru all assign stmts, get their variables
        LIST_OF_STMT_NO listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
        LIST_OF_STMT_NO::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itAssign);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
        LIST_OF_STMT_NO::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var used
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itAssign);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesAssignHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(a, v), modifies(a, _)
        // iterate thru all assign stmts, get their variables
        LIST_OF_STMT_NO listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
        LIST_OF_STMT_NO::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itAssign);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
        LIST_OF_STMT_NO::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var modified
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itAssign);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itAssign);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesStmtHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName == "" || varName == "_") {
        // Case: uses(s, v), uses(s, _)
        // iterate thru all stmts, get their variables
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(i);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(s, "count")
        // iterate thru all stmts, get their variables, check if "count" is inside

        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(i);
            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(i);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesStmtHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;
    StmtNum largestStmt = TypeToStmtNumTable::getLargestStmt();

    if (varName == "" || varName == "_") {
        // Case: modifies(s, v), modifies(s, _)
        // iterate thru all stmts, get their variables
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(i);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(i);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(s, "count")
        // iterate thru all stmts, get their variables, check if "count" is inside
        for (int i = 1; i <= largestStmt; i++) {
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(i);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(i);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesPrintHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(pn, v), uses(pn, _)
        // iterate thru all print stmts, get their variables
        LIST_OF_STMT_NO listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Print);
        LIST_OF_STMT_NO::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itPrint);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itPrint);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(pn, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Print);
        LIST_OF_STMT_NO::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt, get the list of var used
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itPrint);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itPrint);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesReadHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(r, v), modifies(r, _)
        // iterate thru all read stmts, get their variables
        LIST_OF_STMT_NO listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Read);
        LIST_OF_STMT_NO::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itRead);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itRead);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(pn, "count")
        // iterate thru all read stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::Read);
        LIST_OF_STMT_NO::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt, get the list of var modified
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itRead);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itRead);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesWhileHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(w, v), uses(w, _)
        // iterate thru all while stmts, get their variables
        LIST_OF_STMT_NO listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::While);
        LIST_OF_STMT_NO::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itWhile);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(w, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::While);
        LIST_OF_STMT_NO::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var used
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itWhile);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesWhileHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(w, v), modifies(w, _)
        // iterate thru all while stmts, get their variables
        LIST_OF_STMT_NO listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::While);
        LIST_OF_STMT_NO::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            unordered_set<VAR_NAME> listOfVarModifies = ModifyTable::getStmtModify(*itWhile);
            if (!listOfVarModifies.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarModifies));
            }
        }
    } else {
        // Case: modifies(w, "count")
        // iterate thru all while stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfWhileStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::While);
        LIST_OF_STMT_NO::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var modified
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itWhile);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesIfHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(if, v), uses(w, _)
        // iterate thru all if stmts, get their variables
        LIST_OF_STMT_NO listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::If);
        LIST_OF_STMT_NO::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itIf);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::If);
        LIST_OF_STMT_NO::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            unordered_set<VAR_NAME> listOfVarUsed = UseTable::getStmtUse(*itIf);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesIfHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(if, v), modifies(w, _)
        // iterate thru all if stmts, get their variables
        LIST_OF_STMT_NO listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::If);
        LIST_OF_STMT_NO::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itIf);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        LIST_OF_STMT_NO listOfIfStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::If);
        LIST_OF_STMT_NO::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            unordered_set<VAR_NAME> listOfVarModified = ModifyTable::getStmtModify(*itIf);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::usesProcHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(p, v), uses(p, _)
        // iterate thru all procedures, get their variables

        LIST_OF_PROC_NAME listOfProcNames = ProcTable::getAllProcedure();
        LIST_OF_PROC_NAME::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VAR_NAME> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (!listOfVarsUsed.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsUsed));
            }
        }
    } else {
        // Case: uses(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
        LIST_OF_PROC_NAME listOfProcNames = ProcTable::getAllProcedure();
        LIST_OF_PROC_NAME::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VAR_NAME> listOfVarsUsed = UseTable::getProcUse(*itProc);

            if (find(begin(listOfVarsUsed), end(listOfVarsUsed), varName) != end(listOfVarsUsed)) {
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractorHelper::modifiesProcHelper(VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(p, v), modifies(p, _)
        // iterate thru all procedures, get their variables

        LIST_OF_PROC_NAME listOfProcNames = ProcTable::getAllProcedure();
        LIST_OF_PROC_NAME::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VAR_NAME> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (!listOfVarsModified.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsModified));
            }
        }
    } else {
        // Case: modifies(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
        LIST_OF_PROC_NAME listOfProcNames = ProcTable::getAllProcedure();
        LIST_OF_PROC_NAME::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            unordered_set<VAR_NAME> listOfVarsModified = ModifyTable::getProcModify(*itProc);

            if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
                unordered_set<VAR_NAME> varNameUsed = { varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}