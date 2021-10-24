//
// Created by geyul on 23/10/2021.
//

#include <PKB/TypePreDefine.h>
#include "CFGBip.h"

void CFGBip::addEdge(size_t from, size_t to) {
    edgeMap[from].push_back(CFGBipEdge(from, to));
}

CFGBip::CFGBip(size_t V) {
    for (int i = 0; i < V; i++) {
        size_t stmtNo = i + 1;
        stmtNodeMap[stmtNo] = CFGBipNode(stmtNo);
        edgeMap[stmtNo] = vector<CFGBipEdge>();
    }
}

void CFGBip::addBranchLabel(size_t from, size_t to, const vector<size_t>& labels, size_t branchFrom) {
    vector<CFGBipEdge> targetList = edgeMap[from];

    for (auto edge: targetList) {
        if (from == edge.getFromNode() && to == edge.getToNode() && labels == edge.getBranchLabel()) {
            if (branchFrom < 0) {
                vector<size_t> currBranches = edge.getBranchLabel();
                currBranches.pop_back();
                edge.setBranchFrom(currBranches);
            } else {
                edge.setBranchFrom(labels);
            }
        }
    }
}
