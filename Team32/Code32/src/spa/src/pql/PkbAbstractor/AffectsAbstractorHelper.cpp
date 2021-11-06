#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"
#include "AffectsAbstractorHelper.h"
#include "NextAbstractorHelper.h"

bool pql::AffectsAbstractorHelper::isSameProc(StmtNum assignStmtNum1, StmtNum assignStmtNum2) {

    ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
    ListOfProcNames::iterator itProcNames;

    for (itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
        ListOfStmtNos listOfStmtNums = ProcTable::getProcStmtList(*itProcNames);

        if ((listOfStmtNums.find(assignStmtNum1) != listOfStmtNums.end()) && (listOfStmtNums.find(assignStmtNum2) != listOfStmtNums.end())) {
            return true;
        }
    }
    return false;
}

bool pql::AffectsAbstractorHelper::isModifiesUsed(StmtNum assignStmtNum1, StmtNum assignStmtNum2) {
    VarName varModified = *(ModifyTable::getStmtModify(assignStmtNum1).begin());
    ListOfVarNames varsUsed = UseTable::getStmtUse(assignStmtNum2);

    if (varsUsed.find(varModified) != varsUsed.end()) {
        return true;
    }
    return false;
}

bool pql::AffectsAbstractorHelper::isAffectsItself(StmtNum assignStmt, VarName varModified){
    // assign stmts will always have one stmt next
    ListOfProgLines nextList = NextTable::getNext(assignStmt);
    if (nextList.empty()) {
        return false;
    }
    StmtNum nextStmt = *(nextList.begin());

    list<vector<StmtNum>> listOfAllPaths = AffectsAbstractorHelper::getAllPaths(nextStmt, assignStmt);

    if (!listOfAllPaths.empty()) {
        // if there is a path
        bool isVarNotModifiedByAPath = AffectsAbstractorHelper::isVarNotModifiedByAPathCheckFirstNode(listOfAllPaths, varModified);

        if (isVarNotModifiedByAPath) {
            return true;
        }
    }
    return false;
}

list<vector<StmtNum>> pql::AffectsAbstractorHelper::getAllPaths(StmtNum start, StmtNum end) {
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

void pql::AffectsAbstractorHelper::getAllPathsHelper(StmtNum start, StmtNum end, vector<size_t>& isVisited, vector<StmtNum>& currPath, list<vector<StmtNum>>& allPaths) {

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

bool pql::AffectsAbstractorHelper::isStmtModifiesVar(StmtNum stmtNum, VarName varName) {
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

bool pql::AffectsAbstractorHelper::isVarNotModifiedByAPathCheckFirstNode(list<vector<StmtNum>> listOfAllPaths, VarName varName) {
    int start = 0;

    list<vector<StmtNum>>::iterator itPaths;
    for(itPaths = listOfAllPaths.begin(); itPaths != listOfAllPaths.end(); ++itPaths) {
        // for each path
        vector<StmtNum> path = *itPaths;

        if (path.size() == 2) {
            return true;
        }

        for (int i = start; i < path.size() - 1; i++) {
            // for each stmt between start and end
            StmtNum stmtNum = path[i];
            bool isStmtModifiesVar = AffectsAbstractorHelper::isStmtModifiesVar(stmtNum, varName);  // need account for while and if loops

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

bool pql::AffectsAbstractorHelper::isVarNotModifiedByAPathNotCheckFirstNode(list<vector<StmtNum>> listOfAllPaths, VarName varName) {
    int start = 1;

    list<vector<StmtNum>>::iterator itPaths;
    for(itPaths = listOfAllPaths.begin(); itPaths != listOfAllPaths.end(); ++itPaths) {
        // for each path
        vector<StmtNum> path = *itPaths;

        if (path.size() == 2) {
            return true;
        }

        for (int i = start; i < path.size() - 1; i++) {
            // for each stmt between start and end
            StmtNum stmtNum = path[i];
            // need account for while and if loops
            bool isStmtModifiesVar = AffectsAbstractorHelper::isStmtModifiesVar(stmtNum, varName);

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

bool pql::AffectsAbstractorHelper::isAffects(StmtNum stmtNum1, StmtNum stmtNum2) {

    DesignEntity typeOfStmt1 = TypeToStmtNumTable::getTypeOfStmt(stmtNum1);
    DesignEntity typeOfStmt2 = TypeToStmtNumTable::getTypeOfStmt(stmtNum2);

    if (typeOfStmt1 == DesignEntity::ASSIGN && typeOfStmt2 == DesignEntity::ASSIGN) {
        bool isSameProc = AffectsAbstractorHelper::isSameProc(stmtNum1, stmtNum2);
        ListOfVarNames modifiedVarList = ModifyTable::getStmtModify(stmtNum1);
        if (modifiedVarList.empty()) {
            return false;
        }
        VarName varModifiedByA1 = *(modifiedVarList.begin());

        if (isSameProc) {
            bool isModifiesUsed = AffectsAbstractorHelper::isModifiesUsed(stmtNum1, stmtNum2);

            if (isModifiesUsed) {

                if (stmtNum1 == stmtNum2) {
                    // same stmt num
                    bool isAffectsItself = AffectsAbstractorHelper::isAffectsItself(stmtNum1, varModifiedByA1);
                    return isAffectsItself;
                }

                list<vector<StmtNum>> listOfAllPaths = AffectsAbstractorHelper::getAllPaths(stmtNum1, stmtNum2);
                if (!listOfAllPaths.empty()) {
                    // if there is a path
                    bool isVarNotModifiedByAPath = AffectsAbstractorHelper::isVarNotModifiedByAPathNotCheckFirstNode(listOfAllPaths, varModifiedByA1);
                    if (isVarNotModifiedByAPath) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Graph pql::AffectsAbstractorHelper::createAffectsStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    Graph affectsStarGraph;
    affectsStarGraph = PkbAbstractorHelper::initGraph(int(numV));

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            affectsStarGraph[i][j] = AffectsAbstractorHelper::isAffects(i + 1, j + 1);
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

unordered_set<StmtNum> pql::AffectsAbstractorHelper::getAffectsStar(StmtNum assignStmt1, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectsStarList;

    if (assignStmt1 - 1 >= affectsStarGraph.size())
        return affectsStarList;

    for (int j = 0; j < affectsStarGraph[assignStmt1 - 1].size(); j++) {
        int to = j + 1;
        if (affectsStarGraph[assignStmt1 - 1][j] == 1) {
            affectsStarList.insert(to);
        }
    }
    return affectsStarList;
}

unordered_set<StmtNum> pql::AffectsAbstractorHelper::getAffectedByStar(StmtNum assignStmt2, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectedByList;

    if (assignStmt2 - 1 >= affectsStarGraph.size())
        return affectedByList;

    for (int i = 0; i < affectsStarGraph[assignStmt2 - 1].size(); i++) {
        int to = i + 1;
        if (affectsStarGraph[i][assignStmt2 - 1] == 1) {
            affectedByList.insert(to);
        }
    }
    return affectedByList;
}

bool pql::AffectsAbstractorHelper::isAffectsBipItself(StmtNum assignStmt, VarName varModified) {
    // assign stmts will always have one stmt next
    ListOfProgLines nextList = NextBipTable::getNext(assignStmt);
    if (nextList.empty()) {
        return false;
    }
    StmtNum nextStmt = *(nextList.begin());

    list<vector<StmtNum>> listOfAllPaths = AffectsAbstractorHelper::getAllPathsBip(nextStmt, assignStmt);

    if (!listOfAllPaths.empty()) {
        // there is a path
        bool isVarNotModifiedByAPath = AffectsAbstractorHelper::isVarNotModifiedByAPathCheckFirstNode(listOfAllPaths, varModified);

        if (isVarNotModifiedByAPath) {
            return true;
        }
    }
    return false;
}

bool pql::AffectsAbstractorHelper::isAffectsBip(StmtNum stmtNum1, StmtNum stmtNum2) {
    DesignEntity typeOfStmt1 = TypeToStmtNumTable::getTypeOfStmt(stmtNum1);
    DesignEntity typeOfStmt2 = TypeToStmtNumTable::getTypeOfStmt(stmtNum2);

    if (typeOfStmt1 == DesignEntity::ASSIGN && typeOfStmt2 == DesignEntity::ASSIGN) {
        ListOfVarNames modifiedVarList = ModifyTable::getStmtModify(stmtNum1);
        if (modifiedVarList.empty()) {
            return false;
        }
        VarName varModifiedByA1 = *(modifiedVarList.begin());


        bool isModifiesUsed = AffectsAbstractorHelper::isModifiesUsed(stmtNum1, stmtNum2);
        if (isModifiesUsed) {

            if (stmtNum1 == stmtNum2) {
                // same stmt num
                bool isAffectsItself = AffectsAbstractorHelper::isAffectsBipItself(stmtNum1, varModifiedByA1);
                return isAffectsItself;
            }

            list<vector<StmtNum>> listOfAllPaths = AffectsAbstractorHelper::getAllPathsBip(stmtNum1, stmtNum2);
            if (!listOfAllPaths.empty()) {
                // if there is a path
                bool isVarNotModifiedByAPath = AffectsAbstractorHelper::isVarNotModifiedByAssignment(listOfAllPaths, varModifiedByA1,false);

                if (isVarNotModifiedByAPath) {
                    return true;
                }
            }
        }

    }
    return false;
}

list<std::vector<StmtNum>> pql::AffectsAbstractorHelper::getAllPathsBip(StmtNum start, StmtNum end) {
    vector<vector<size_t>> possibleStartBranches = NextAbstractorHelper::getAllPossibleStartLabel(start);
    list<vector<StmtNum>> allPaths;
    for (auto branches: possibleStartBranches) {
        vector<StmtNum> currPath;
        list<vector<StmtNum>> currAllPath;
        unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap = CFGBipTable::getEdgeMap();
        size_t size = edgeMap.size();
        vector<vector<bool>> isVisited = {size + 1, vector<bool>(size, false)};;
        getAllPathsBipHelper(start, end, branches.back(), isVisited, currPath, currAllPath, branches);
        allPaths.insert(allPaths.end(), currAllPath.begin(), currAllPath.end());
    }
    return allPaths;
}

Graph pql::AffectsAbstractorHelper::createAffectsBipStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    Graph affectsStarGraph;
    affectsStarGraph = PkbAbstractorHelper::initGraph(int(numV));
    Graph nextBipStarGraph = pql::PkbAbstractorHelper::getGraph("nextBipStar");
    if (nextBipStarGraph.empty()) {
        nextBipStarGraph = pql::NextAbstractorHelper::createNextBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextBipStar", nextBipStarGraph);
    }

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            affectsStarGraph[i][j] = AffectsAbstractorHelper::isAffectsBip(i + 1, j + 1) && nextBipStarGraph[i][j];
        }
    }

    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                if (nextBipStarGraph[i][j] == 0) {
                    affectsStarGraph[i][j] = 0;
                } else {
                    affectsStarGraph[i][j] = (affectsStarGraph[i][j] == 1) ||
                            ((affectsStarGraph[i][k] == 1) && affectsStarGraph[k][j] == 1) ? 1 : 0;
                }
            }
        }
    }
    return affectsStarGraph;
}

std::unordered_set<StmtNum> pql::AffectsAbstractorHelper::getAffectsBipStar(StmtNum assignStmt1, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectsStarList;

    if (assignStmt1 - 1 >= affectsStarGraph.size())
        return affectsStarList;

    for (int j = 0; j < affectsStarGraph[assignStmt1 - 1].size(); j++) {
        int to = j + 1;
        if (affectsStarGraph[assignStmt1 - 1][j] == 1) {
            affectsStarList.insert(to);
        }
    }
    return affectsStarList;
}

std::unordered_set<StmtNum> pql::AffectsAbstractorHelper::getAffectedBipByStar(StmtNum assignStmt2, Graph affectsStarGraph) {
    unordered_set<StmtNum> affectedByList;

    if (assignStmt2 - 1 >= affectsStarGraph.size())
        return affectedByList;

    for (int i = 0; i < affectsStarGraph[assignStmt2 - 1].size(); i++) {
        int to = i + 1;
        if (affectsStarGraph[i][assignStmt2 - 1] == 1) {
            affectedByList.insert(to);
        }
    }
    return affectedByList;
}

bool pql::AffectsAbstractorHelper::isVarNotModifiedByAssignment(list<vector<StmtNum>> listOfAllPaths, VarName varName,
                                                                bool isCheckFirstNode) {
    int start;
    unordered_map<StmtNum, DesignEntity> stmtTypeMap = TypeToStmtNumTable::getStmtToTypeMap();
    if (isCheckFirstNode) {
        start = 0;
    } else {
        start = 1;
    }

    list<vector<StmtNum>>::iterator itPaths;
    for(itPaths = listOfAllPaths.begin(); itPaths != listOfAllPaths.end(); ++itPaths) {
        // for each path
        vector<StmtNum> path = *itPaths;

        if (path.size() == 2) {
            return true;
        }

        for (int i = start; i < path.size() - 1; i++) {
            // for each stmt between start and end
            StmtNum stmtNum = path[i];
            bool isStmtModifiesVar;
            if (stmtTypeMap[stmtNum] != DesignEntity::ASSIGN) {
                isStmtModifiesVar = false;
            } else {
                isStmtModifiesVar = AffectsAbstractorHelper::isStmtModifiesVar(stmtNum, varName);
            }

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

void pql::AffectsAbstractorHelper::getAllPathsBipHelper(StmtNum start, StmtNum end, size_t label, vector<vector<bool>>& isVisited, vector<StmtNum>& currPath,
                                                        list<std::vector<StmtNum>>& allPaths, vector<size_t>& branches) {
    unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap = CFGBipTable::getEdgeMap();
    size_t currBranch = branches.back();
    vector<size_t> currBranchList = vector<size_t> (branches.size());
    std::copy(branches.begin(), branches.end(), currBranchList.begin());
    size_t size = edgeMap.size();
    size_t tag = currBranch == 0 ? size : currBranch - 1;
    int labelInt = (int) label;
    unordered_map<StmtNo, ProcName> stmtCallTable = CallStmtTable::getCallStmtToProcMap();
    unordered_set<StmtNo> callStmtSet;
    for (const auto& kv: stmtCallTable) {
        callStmtSet.insert(kv.first);
    }

    if (isVisited[tag][start - 1] == 1) {
        return;
    }

    isVisited[tag][start - 1] = true;
    currPath.push_back(start);

    if (start == end) {
        // reached the end
        allPaths.push_back(currPath);
        isVisited[tag][start - 1] = false;

        // If end with an branch back edge
        if (labelInt < 0) {
            branches.push_back(-labelInt);
        }
        currPath.pop_back();

        // Pop if the last is the branch out edge
        if (callStmtSet.find(currPath.back()) != callStmtSet.end()) {
            branches.pop_back();
        }

        return;
    }

    if (callStmtSet.find(start) != callStmtSet.end()) {
        branches.push_back(start);
    }
    unordered_set<CFGBipEdge> nextList = edgeMap[start];
    unordered_set<CFGBipEdge>::iterator itNextList;

    for (itNextList = nextList.begin(); itNextList != nextList.end(); ++itNextList) {
        int nextLabel = int(itNextList -> branchLabel);
        if (nextLabel != branches.back() && -nextLabel != branches.back()) {
            // Skip edge that not in the same branch
            continue;
        }
        if (nextLabel < 0 && -nextLabel == branches.back()) {
            branches.pop_back();
        }
        getAllPathsBipHelper(itNextList->to, end, itNextList->branchLabel, isVisited, currPath, allPaths, branches);
    }

    branches.clear();
    for (auto ele: currBranchList) {
        branches.push_back(ele);
    }
    currPath.pop_back();
    isVisited[tag][start - 1] = false;
}
