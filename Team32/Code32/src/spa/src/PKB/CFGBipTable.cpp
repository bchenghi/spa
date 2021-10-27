//
// Created by Jerry Lin on 27/10/21.
//

#include "CFGBipTable.h"


Graph CFGBipTable::getCFGBip() {
    return cfgBip;
}

void CFGBipTable::setCFGBip(const Graph &graph) {
    cfgBip = graph;
}

void CFGBipTable::clear() {
    cfgBip.clear();
}

