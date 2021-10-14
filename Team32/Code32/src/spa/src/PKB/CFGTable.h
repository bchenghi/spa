#ifndef GUARD_CFG_TABLE_H
#define GUARD_CFG_TABLE_H

#include "simple/SourceProcessor/CFG.h"

typedef vector<vector<size_t>> Graph;

class CFGTable {
public:
    static Graph getCFG();
    static void setCFG(const Graph &graph);
    static void clear();
private:
    static Graph cfg;
};

#endif
