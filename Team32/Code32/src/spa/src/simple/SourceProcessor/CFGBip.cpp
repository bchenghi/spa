#include <PKB/TypePreDefine.h>

#include <utility>
#include "CFGBip.h"

void CFGBip::addEdge(size_t from, size_t to, size_t branchLabel) {
    edgeMap[from].insert(CFGBipEdge({from, to, branchLabel}));
}

CFGBip::CFGBip(size_t V) {
    for (int i = 0; i < V; i++) {
        size_t stmtNo = i + 1;
        edgeMap[stmtNo] = unordered_set<CFGBipEdge>();
    }
}

size_t CFGBip::addDummyNode() {
    size_t currSize = edgeMap.size();
    edgeMap[currSize + 1] = unordered_set<CFGBipEdge>();
    return currSize + 1;
}

Graph CFGBip::getCFGBipGraph() {
    size_t V = edgeMap.size();
    Graph graph;

    for (int i = 0; i < V; i++) {
        vector<size_t> row;
        for (int j = 0; j < V; j++) {
            row.push_back(0);
        }
        graph.push_back(row);
    }

    for (int i = 0; i < V; i++) {
        size_t stmtNum = i + 1;
        unordered_set<CFGBipEdge> edges = edgeMap[stmtNum];

        for (const auto& edge: edges) {
            size_t targetStmtNo = edge.to;
            graph[i][targetStmtNo - 1] = 1;
        }
    }

    return graph;
}

unordered_map<size_t, unordered_set<CFGBipEdge>> CFGBip::getEdgeMap() {
    return edgeMap;
}
