//
// Created by geyul on 23/10/2021.
//

#include <PKB/TypePreDefine.h>
#include "CFGBip.h"

void CFGBip::addEdge(size_t from, size_t to, vector<size_t> branchLabels) {
    edgeMap[from].push_back(CFGBipEdge(from, to, branchLabels));
}

CFGBip::CFGBip(size_t V, size_t stmtListSize) {
    for (int i = 0; i < V; i++) {
        size_t stmtNo = i + 1;
        stmtNodeMap[stmtNo] = CFGBipNode(stmtNo);
        edgeMap[stmtNo] = vector<CFGBipEdge>();
    }

    stmtListSize = V;
}

bool CFGBip::isDummyNode(size_t nodeId) {
    return nodeId > stmtListSize;
}

size_t CFGBip::addDummyNode() {
    size_t currSize = stmtNodeMap.size();
    stmtNodeMap[currSize] = CFGBipNode(currSize);
    return currSize;
}

Graph CFGBip::getCFGBipGraph() {
    size_t V = stmtNodeMap.size();
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
        vector<CFGBipEdge> edges = edgeMap[stmtNum];

        for (auto edge: edges) {
            size_t targetStmtNo = edge.getToNode();
            graph[i][targetStmtNo - 1] = 1;
        }
    }

    return graph;
}
