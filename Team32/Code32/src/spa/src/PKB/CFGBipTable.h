//
// Created by Jerry Lin on 27/10/21.
//

#ifndef AUTOTESTER_CFGBIPTABLE_H
#define AUTOTESTER_CFGBIPTABLE_H

#include "simple/SourceProcessor/CFGBip/CFGBip.h"

class CFGBipTable {
public:
    static CFGBip getCFGBip();
    static void setCFGBip(const CFGBip& cfgBip);
private:
    static CFGBip cfgBip;
};


#endif //AUTOTESTER_CFGBIPTABLE_H
