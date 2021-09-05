#include "PkbAbstractorHelper.h"
#include "PkbAbstractor.h"

bool pql::PkbAbstractorHelper::isNum(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesProcNameHelper(string procName, VarName varName) {
    list<pair<string, list<string>>> result;
    if (varName == "" || varName == "_") {
        // Case: uses(procName, v), uses(procName, _)
        list<VarName> listOfVarsUsed = PkbAbstractor::usesTable.procUses(procName);
        if (!listOfVarsUsed.empty()) {
            result.push_back(make_pair(procName, listOfVarsUsed));
        }
    } else {
        // Case: uses(procName, varName)
        list<VarName> listOfVarsUsed = PkbAbstractor::usesTable.procUses(procName);
        if (find(begin(listOfVarsUsed), end(listOfVarsUsed), varName) != end(listOfVarsUsed)) {
            // varName is in var used list
            list<string> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesProcNameHelper(string procName, VarName varName) {
    list<pair<string, list<string>>> result;
    if (varName == "" || varName == "_") {
        // Case: modifies(procName, v), modifies(procName, _)
        list<VarName> listOfVarsModified = PkbAbstractor::modifiesTable.procModifies(procName);
        if (!listOfVarsModified.empty()) {
            result.push_back(make_pair(procName, listOfVarsModified));
        }
    } else {
        // Case: modifies(procName, varName)
        list<VarName> listOfVarsModified = PkbAbstractor::modifiesTable.procModifies(procName);
        if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
            // varName is in var modifies list
            list<string> varNameUsed = { varName };
            result.push_back(make_pair(procName, varNameUsed));
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesStmtNumHelper(StmtNum stmtNum, VarName varName) {
    list<pair<string, list<string>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName == "" || varName == "_") {
        // Case: uses(2, v), uses(2, _)
        list<VarName> listOfVarsStmtUses = PkbAbstractor::usesTable.stmtUses(stmtNum);

        if (!listOfVarsStmtUses.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtUses));
        }
    } else {
        // Case: uses(2, "count")
        list<VarName> listOfVarsStmtUses = PkbAbstractor::usesTable.stmtUses(stmtNum);
        if (find(begin(listOfVarsStmtUses), end(listOfVarsStmtUses), varName) != end(listOfVarsStmtUses)) {
            // "count" is in var used list
            list<string> varNameUsed = { varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesStmtNumHelper(StmtNum stmtNum, VarName varName) {
    list<pair<string, list<string>>> result;
    string stmtNumStr = std::to_string(stmtNum);

    if (varName == "" || varName == "_") {
        // Case: modifies(2, v), modifies(2, _)
        list<VarName> listOfVarsStmtModifies = PkbAbstractor::modifiesTable.stmtModifies(stmtNum);

        if (!listOfVarsStmtModifies.empty()) {
            result.push_back(make_pair(stmtNumStr, listOfVarsStmtModifies));
        }
    } else {
        // Case: modifies(2, "count")
        list<VarName> listOfVarsStmtModifies = PkbAbstractor::modifiesTable.stmtModifies(stmtNum);
        if (find(begin(listOfVarsStmtModifies), end(listOfVarsStmtModifies), varName) != end(listOfVarsStmtModifies)) {
            // "count" is in var modifies list
            list<string> varNameUsed = { varName };
            result.push_back(make_pair(stmtNumStr, varNameUsed));
        }
    }
    return result;
}


list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesDesignEntityHelper(DesignEntity designEntity, VarName varName) {
    // LHS is Design entity
    list<pair<string, list<string>>> result;

    switch(designEntity) {
        case DesignEntity::Assign:
            result = usesAssignHelper(varName);
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
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesDesignEntityHelper(DesignEntity designEntity, VarName varName) {
    // LHS is Design entity
    list<pair<string, list<string>>> result;

    switch(designEntity) {
        case DesignEntity::Assign:
            result = modifiesAssignHelper(varName);
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
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesAssignHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(a, v), uses(a, _)
        // iterate thru all assign stmts, get their variables
        list<StmtNum> listOfAssignStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Assign);
        list<StmtNum>::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itAssign);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfAssignStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Assign);
        list<StmtNum>::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var used
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itAssign);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itAssign);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }

    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesAssignHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(a, v), modifies(a, _)
        // iterate thru all assign stmts, get their variables
        list<StmtNum> listOfAssignStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Assign);
        list<StmtNum>::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itAssign);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itAssign);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(a, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfAssignStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Assign);
        list<StmtNum>::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            // for each assign stmt, get the list of var used
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itAssign);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itAssign);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesPrintHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(pn, v), uses(pn, _)
        // iterate thru all print stmts, get their variables
        list<StmtNum> listOfPrintStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Print);
        list<StmtNum>::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itPrint);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itPrint);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(pn, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfPrintStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Print);
        list<StmtNum>::iterator itPrint;

        for (itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
            // for each print stmt, get the list of var used
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itPrint);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itPrint);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesReadHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(r, v), modifies(r, _)
        // iterate thru all read stmts, get their variables
        list<StmtNum> listOfReadStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Read);
        list<StmtNum>::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itRead);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itRead);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(pn, "count")
        // iterate thru all read stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfReadStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::Read);
        list<StmtNum>::iterator itRead;

        for (itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
            // for each read stmt, get the list of var modified
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itRead);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var modified list
                string stmtNum = std::to_string(*itRead);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesWhileHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(w, v), uses(w, _)
        // iterate thru all while stmts, get their variables
        list<StmtNum> listOfWhileStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::While);
        list<StmtNum>::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itWhile);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(w, "count")
        // iterate thru all assign stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfWhileStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::While);
        list<StmtNum>::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var used
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itWhile);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesWhileHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(w, v), modifies(w, _)
        // iterate thru all while stmts, get their variables
        list<StmtNum> listOfWhileStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::While);
        list<StmtNum>::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt
            list<VarName> listOfVarModifies = PkbAbstractor::modifiesTable.stmtModifies(*itWhile);
            if (!listOfVarModifies.empty()) {
                string stmtNum = std::to_string(*itWhile);
                result.push_back(make_pair(stmtNum, listOfVarModifies));
            }
        }
    } else {
        // Case: modifies(w, "count")
        // iterate thru all while stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfWhileStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::While);
        list<StmtNum>::iterator itWhile;

        for (itWhile = listOfWhileStmts.begin(); itWhile != listOfWhileStmts.end(); ++itWhile) {
            // for each while stmt, get the list of var modified
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itWhile);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itWhile);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesIfHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(if, v), uses(w, _)
        // iterate thru all if stmts, get their variables
        list<StmtNum> listOfIfStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::If);
        list<StmtNum>::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itIf);
            if (!listOfVarUsed.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarUsed));
            }
        }
    } else {
        // Case: uses(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfIfStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::If);
        list<StmtNum>::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            list<VarName> listOfVarUsed = PkbAbstractor::usesTable.stmtUses(*itIf);

            if (find(begin(listOfVarUsed), end(listOfVarUsed), varName) != end(listOfVarUsed)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesIfHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(if, v), modifies(w, _)
        // iterate thru all if stmts, get their variables
        list<StmtNum> listOfIfStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::If);
        list<StmtNum>::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each while stmt
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itIf);
            if (!listOfVarModified.empty()) {
                string stmtNum = std::to_string(*itIf);
                result.push_back(make_pair(stmtNum, listOfVarModified));
            }
        }
    } else {
        // Case: modifies(if, "count")
        // iterate thru all if stmts, get their variables, check if "count" is inside
        list<StmtNum> listOfIfStmts = PkbAbstractor::typeToStmtNoTable.getStmtWithType(DesignEntity::If);
        list<StmtNum>::iterator itIf;

        for (itIf = listOfIfStmts.begin(); itIf != listOfIfStmts.end(); ++itIf) {
            // for each if stmt, get the list of var used
            list<VarName> listOfVarModified = PkbAbstractor::modifiesTable.stmtModifies(*itIf);

            if (find(begin(listOfVarModified), end(listOfVarModified), varName) != end(listOfVarModified)) {
                // "count" is in var used list
                string stmtNum = std::to_string(*itIf);
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(stmtNum, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::usesProcHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: uses(p, v), uses(p, _)
        // iterate thru all procedures, get their variables

        list<string> listOfProcNames = PkbAbstractor::procTable.getAllProcedure();
        list<string>::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            list<VarName> listOfVarsUsed = PkbAbstractor::usesTable.procUses(*itProc);

            if (!listOfVarsUsed.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsUsed));
            }
        }
    } else {
        // Case: uses(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
        list<string> listOfProcNames = PkbAbstractor::procTable.getAllProcedure();
        list<string>::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            list<VarName> listOfVarsUsed = PkbAbstractor::usesTable.procUses(*itProc);

            if (find(begin(listOfVarsUsed), end(listOfVarsUsed), varName) != end(listOfVarsUsed)) {
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}

list<pair<string, list<string>>> pql::PkbAbstractorHelper::modifiesProcHelper(VarName varName) {
    list<pair<string, list<string>>> result;

    if (varName == "" || varName == "_") {
        // Case: modifies(p, v), modifies(p, _)
        // iterate thru all procedures, get their variables

        list<string> listOfProcNames = PkbAbstractor::procTable.getAllProcedure();
        list<string>::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            list<VarName> listOfVarsModified = PkbAbstractor::modifiesTable.procModifies(*itProc);

            if (!listOfVarsModified.empty()) {
                result.push_back(make_pair(*itProc, listOfVarsModified));
            }
        }
    } else {
        // Case: modifies(p, "count")
        // iterate thru all proc, get their variables, check if "count" is inside
        list<string> listOfProcNames = PkbAbstractor::procTable.getAllProcedure();
        list<string>::iterator itProc;

        for (itProc = listOfProcNames.begin(); itProc != listOfProcNames.end(); ++itProc) {
            list<VarName> listOfVarsModified = PkbAbstractor::modifiesTable.procModifies(*itProc);

            if (find(begin(listOfVarsModified), end(listOfVarsModified), varName) != end(listOfVarsModified)) {
                list<string> varNameUsed = { varName };
                result.push_back(make_pair(*itProc, varNameUsed));
            }
        }
    }
    return result;
}