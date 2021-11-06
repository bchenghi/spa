#ifndef AUTOTESTER_CFGBIPTABLE_H
#define AUTOTESTER_CFGBIPTABLE_H

#include "simple/SourceProcessor/CFGBip.h"

class CFGBipTable {
public:
    static Graph getCFGBip();
    static void setCFGBip(const Graph &graph);
    static void setEdgeMap(const unordered_map<size_t, unordered_set<CFGBipEdge>> &map);
    static unordered_map<size_t, unordered_set<CFGBipEdge>> getEdgeMap();
    static void clear();
private:
    static Graph cfgBip;
    static unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap;
};


#endif
