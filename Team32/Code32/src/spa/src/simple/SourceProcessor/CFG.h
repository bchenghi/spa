//
// Created by geyul on 5/10/2021.
//

#ifndef GUARD_CFG_H
#define GUARD_CFG_H

#include <vector>
using namespace std;

typedef vector<vector<size_t>> Graph;

class CFG {
public:
    void addEdge(size_t from, size_t to);
    Graph getCFG();
    void initCFG(size_t size);
    size_t addDummyNode();
private:
    Graph graph;
};


#endif
