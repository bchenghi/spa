//
// Created by Jerry Lin on 27/10/21.
//

#include "CFGBipTable.h"

Graph CFGBipTable::cfgBip;

unordered_map<size_t, unordered_set<CFGBipEdge>> CFGBipTable::edgeMap;

Graph CFGBipTable::getCFGBip() {
    return cfgBip;
}

void CFGBipTable::setCFGBip(const Graph &graph) {
    cfgBip = graph;
}

void CFGBipTable::clear() {
    cfgBip.clear();
}

void CFGBipTable::setEdgeMap(const unordered_map<size_t, unordered_set<CFGBipEdge>> &map) {
    edgeMap = map;
}

unordered_map<size_t, unordered_set<CFGBipEdge>> CFGBipTable::getEdgeMap() {
    return edgeMap;
}

