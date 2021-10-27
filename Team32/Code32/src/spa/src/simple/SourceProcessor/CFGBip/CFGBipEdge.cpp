//
// Created by geyul on 24/10/2021.
//

#include <cstddef>
#include <utility>
#include "CFGBipEdge.h"

CFGBipEdge::CFGBipEdge(size_t fromNode, size_t to, vector<size_t> branchFrom) {
    this->from = fromNode;
    this->to = to;
    this->labelBranchFrom = branchFrom;
}

size_t CFGBipEdge::getFromNode() {
    return from;
}

size_t CFGBipEdge::getToNode() {
    return to;
}




