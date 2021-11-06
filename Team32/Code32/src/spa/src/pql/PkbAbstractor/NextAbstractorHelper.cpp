#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"
#include "NextAbstractorHelper.h"
#include "set"

Graph pql::NextAbstractorHelper::createNextStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    Graph nextStarGraph;
    nextStarGraph = PkbAbstractorHelper::initGraph(int(numV));

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

unordered_set<ProcLine> pql::NextAbstractorHelper::getNextStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> nextStarList;

    if (procLine - 1 >= nextStarGraph.size())
        return nextStarList;

    for (int j = 0; j < nextStarGraph[procLine - 1].size(); j++) {
        int to = j + 1;
        if (nextStarGraph[procLine - 1][j] == 1) {
            nextStarList.insert(to);
        }
    }
    return nextStarList;
}

unordered_set<ProcLine> pql::NextAbstractorHelper::getPrevStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> prevStarList;

    if (procLine - 1 >= nextStarGraph.size())
        return prevStarList;

    for (int i = 0; i < nextStarGraph[procLine - 1].size(); i++) {
        int to = i + 1;
        if (nextStarGraph[i][procLine - 1] == 1) {
            prevStarList.insert(to);
        }
    }
    return prevStarList;
}

Graph pql::NextAbstractorHelper::createNextBipStarGraph() {
    // Modified Floyd Warshall with a boolean array
    size_t numV = TypeToStmtNumTable::getLargestStmt();
    unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap = CFGBipTable::getEdgeMap();
    Graph nextBipStarGraph;
    nextBipStarGraph = PkbAbstractorHelper::initGraph(int(numV));

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            nextBipStarGraph[i][j] = NextBipTable::isNext(i+1, j+1);
        }
    }

    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                nextBipStarGraph[i][j] = (nextBipStarGraph[i][j] == 1) ||
                        ((nextBipStarGraph[i][k] == 1) && nextBipStarGraph[k][j] == 1) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            if (nextBipStarGraph[i][j] == 1 && !hasPath(edgeMap, i, j)) {
                nextBipStarGraph[i][j] = 0;
            }
        }
    }
    return nextBipStarGraph;
}

unordered_set<ProcLine> pql::NextAbstractorHelper::getNextBipStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> nextStarList;

    if (procLine - 1 >= nextStarGraph.size())
        return nextStarList;

    for (int j = 0; j < nextStarGraph[procLine - 1].size(); j++) {
        int to = j + 1;
        if (nextStarGraph[procLine - 1][j] == 1) {
            nextStarList.insert(to);
        }
    }
    return nextStarList;
}

unordered_set<ProcLine> pql::NextAbstractorHelper::getPrevBipStar(ProcLine procLine, Graph nextStarGraph) {
    unordered_set<ProcLine> prevStarList;

    if (procLine - 1 >= nextStarGraph.size())
        return prevStarList;

    for (int i = 0; i < nextStarGraph[procLine - 1].size(); i++) {
        int to = i + 1;
        if (nextStarGraph[i][procLine - 1] == 1) {
            prevStarList.insert(to);
        }
    }
    return prevStarList;
}

bool pql::NextAbstractorHelper::hasPath(unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap,
                                       size_t from, size_t to) {
    size_t fromNo = from + 1;
    size_t toNo = to + 1;
    size_t size = edgeMap.size();
    vector<vector<bool>> visited = {size + 1, vector<bool>(size, false)};
    unordered_map<StmtNo, ProcName> stmtCallTable = CallStmtTable::getCallStmtToProcMap();
    unordered_set<StmtNo> callStmtSet;
    for (const auto& kv: stmtCallTable) {
        callStmtSet.insert(kv.first);
    }
    vector<vector<size_t>> possibleStartLabels = getAllPossibleStartLabel(fromNo);

    for (auto startLabel: possibleStartLabels) {
        queue<size_t> frontier;
        frontier.push(fromNo);
        vector<size_t> labels;
        labels = startLabel;
        // init with no branching
        while (!frontier.empty()) {
            size_t currStmt = frontier.front();

            if (currStmt == toNo) {
                size_t tag = labels.back() == 0? size : labels.back() - 1;
                if (currStmt == fromNo) {
                    return visited[tag][fromNo];
                } else {
                    return true;
                }
            }

            frontier.pop();
            unordered_set<CFGBipEdge> currOutEdges = edgeMap[currStmt];
            size_t branchTag = labels.back() - 1;
            if (labels.back() == 0) {
                branchTag = size;
            }
            visited[branchTag][currStmt - 1] = true;

            for (auto edge: currOutEdges) {
                size_t target = edge.to;
                size_t label = edge.branchLabel;

                size_t tag = label < 0 ? labels.back() - 1 : label - 1;
                if (int(tag) < 0) {
                    tag = size;
                }
                // Skip if visited
                if (visited[tag][target - 1]) {
                    continue;
                }

                if (callStmtSet.find(currStmt) != callStmtSet.end()) {
                    // Branch in
                    labels.push_back(currStmt);
                    frontier.push(target);
                } else {
                    // Check whether is branch back node
                    if (int(label) < 0 && -int(label) == labels.back()) {
                        labels.pop_back();
                        frontier.push(target);
                    }

                    if (label == labels.back()) {
                        frontier.push(target);
                    }
                }
            }
        }
    }
    return false;
}

std::vector<std::vector<size_t>> pql::NextAbstractorHelper::getAllPossibleStartLabel(StmtNum stmtNum) {
    unordered_map<StmtNo, unordered_set<CFGBipEdge>> edgeMap = CFGBipTable::getEdgeMap();
    size_t size = edgeMap.size();
    vector<vector<bool>> visited = {size + 1, vector<bool>(size, false)};
    unordered_map<StmtNo, ProcName> stmtCallTable = CallStmtTable::getCallStmtToProcMap();
    unordered_set<StmtNo> callStmtSet;
    vector<vector<size_t>> result;

    for (const auto& kv: stmtCallTable) {
        callStmtSet.insert(kv.first);
    }

    for (int i = 0; i < size; i++) {
        size_t start = i + 1;
        queue<size_t> frontier;
        frontier.push(start);
        vector<size_t> labels;
        labels.push_back(0);
        while (!frontier.empty()) {
            size_t currStmt = frontier.front();

            if (currStmt == stmtNum) {
                result.push_back(labels);
            }

            frontier.pop();
            unordered_set<CFGBipEdge> currOutEdges = edgeMap[currStmt];
            size_t branchTag = labels.back() - 1;
            if (labels.back() == 0) {
                branchTag = size;
            }
            visited[branchTag][currStmt - 1] = true;

            for (auto edge: currOutEdges) {
                size_t target = edge.to;
                size_t label = edge.branchLabel;

                size_t tag = label < 0 ? labels.back() - 1 : label - 1;
                if (int(tag) < 0) {
                    tag = size;
                }
                // Skip if visited
                if (visited[tag][target - 1]) {
                    continue;
                }

                if (callStmtSet.find(currStmt) != callStmtSet.end()) {
                    // Branch in
                    labels.push_back(currStmt);
                    frontier.push(target);
                } else {
                    // Check whether is branch back node
                    if (int(label) < 0 && -int(label) == labels.back()) {
                        labels.pop_back();
                        frontier.push(target);
                    }

                    if (label == labels.back()) {
                        frontier.push(target);
                    }
                }
            }
        }
        labels.clear();
    }

    return result;
}
