//
// Created by geyul on 23/10/2021.
//

#include <PKB/TypePreDefine.h>

#include <utility>
#include "CFGBip.h"

void CFGBip::addEdge(size_t from, size_t to, vector<size_t> branchLabels) {
    edgeMap[from].insert(CFGBipEdge({from, to, std::move(branchLabels)}));
}

CFGBip::CFGBip(size_t V, size_t stmtListSize) {
    for (int i = 0; i < V; i++) {
        size_t stmtNo = i + 1;
        edgeMap[stmtNo] = unordered_set<CFGBipEdge>();
    }

    this -> stmtListSize = stmtListSize;
}

bool CFGBip::isDummyNode(size_t nodeId) {
    return nodeId > stmtListSize;
}

size_t CFGBip::addDummyNode() {
    size_t currSize = edgeMap.size();
    edgeMap[currSize] = unordered_set<CFGBipEdge>();
    return currSize;
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
