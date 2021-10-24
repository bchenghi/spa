//
// Created by geyul on 24/10/2021.
//

#ifndef GUARD_CFGBIPNODE_H
#define GUARD_CFGBIPNODE_H


#include <cstddef>

class CFGBipNode {
public:
    explicit CFGBipNode(size_t id);
    size_t getId();
private:
    size_t id;
};


#endif