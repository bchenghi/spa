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
