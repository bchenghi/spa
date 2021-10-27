//
// Created by geyul on 24/10/2021.
//

#ifndef GUARD_CFGBIPEDGE_H
#define GUARD_CFGBIPEDGE_H

#include <vector>

using namespace std;

class CFGBipEdge {
public:
    CFGBipEdge(size_t fromNode, size_t to, vector<size_t> branchFrom);

    size_t getFromNode();
    size_t getToNode();
private:
    size_t from;
    size_t to;
    vector<size_t> labelBranchFrom;
};


#endif
