//
// Created by Jerry Lin on 27/10/21.
//

#ifndef AUTOTESTER_CFGBIPTABLE_H
#define AUTOTESTER_CFGBIPTABLE_H

#include "simple/SourceProcessor/CFGBip.h"

class CFGBipTable {
public:
    static Graph getCFGBip();
    static void setCFGBip(const Graph &graph);
    static void clear();
private:
    static Graph cfgBip;
};


#endif //AUTOTESTER_CFGBIPTABLE_H
