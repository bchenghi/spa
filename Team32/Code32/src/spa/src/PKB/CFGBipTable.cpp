//
// Created by Jerry Lin on 27/10/21.
//

#include "CFGBipTable.h"

void CFGBipTable::setCFGBip(const CFGBip & graph) {
    cfgBip = graph;
}

CFGBip CFGBipTable::getCFGBip() {
    return cfgBip;
}
