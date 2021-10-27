//
// Created by geyul on 23/10/2021.
//
#ifndef GUARD_CFGBIP_H
#define GUARD_CFGBIP_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "simple/SourceProcessor/CFG.h"
#include "string"
#include "CFGBipEdge.h"
using namespace std;

typedef vector<vector<size_t>> Graph;

class CFGBip {
public:
    CFGBip(size_t V, size_t stmtListSize);
    void addEdge(size_t from, size_t to, vector<size_t> branchLabels);
    size_t addDummyNode();
    bool isDummyNode(size_t nodeIndex);
    Graph getCFGBipGraph();
private:
    unordered_map<size_t, vector<CFGBipEdge>> edgeMap;
    size_t stmtListSize;
};


#endif