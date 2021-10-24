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
#include "CFGBipNode.h"
using namespace std;

typedef vector<vector<size_t>> Graph;
typedef unordered_map<size_t, vector<unordered_map<StmtNo, size_t>>> ReplicaMap;

class CFGBip {
public:
    explicit CFGBip(size_t V);
    void addEdge(size_t from, size_t to);
    void addBranchLabel(size_t from, size_t to, const vector<size_t>& labels, size_t branchFrom);
private:
    unordered_map<size_t, CFGBipNode> stmtNodeMap;
    unordered_map<size_t, vector<CFGBipEdge>> edgeMap;
};


#endif