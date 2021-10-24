//
// Created by geyul on 24/10/2021.
//

#include "CFGBipNode.h"

CFGBipNode::CFGBipNode(size_t id) {
    this->id = id;
}

size_t CFGBipNode::getId() {
    return this->id;
}

CFGBipNode::CFGBipNode() {
    this -> id = -1;
}
