//
// Created by geyul on 24/10/2021.
//

#include <cstddef>
#include "CFGBipEdge.h"

CFGBipEdge::CFGBipEdge(size_t fromNode, size_t to) {
    this->from = fromNode;
    this->to = to;
    this->labelBranchFrom = vector<size_t>();
}

size_t CFGBipEdge::getFromNode() {
    return from;
}

size_t CFGBipEdge::getToNode() {
    return to;
}

vector<size_t> CFGBipEdge::getBranchLabel() {
    return labelBranchFrom;
}

void CFGBipEdge::setBranchFrom(vector<size_t> branchFrom) {
    for (auto branch: branchFrom) {
        this->labelBranchFrom.push_back(branch);
    }
}




