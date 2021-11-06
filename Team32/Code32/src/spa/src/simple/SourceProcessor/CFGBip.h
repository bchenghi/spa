#ifndef GUARD_CFGBIP_H
#define GUARD_CFGBIP_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "simple/SourceProcessor/CFG.h"
#include "string"
using namespace std;

typedef vector<vector<size_t>> Graph;

struct CFGBipEdge {
    size_t from;
    size_t to;
    size_t branchLabel;

    bool operator==(const CFGBipEdge &other) const {
        return (from == other.from && to == other.to && branchLabel == other.branchLabel);
    }
};

namespace std {
    template <>
    struct hash<CFGBipEdge>
            {
        std::size_t operator()(const CFGBipEdge& k) const
        {
            using std::size_t;
            using std::hash;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<size_t>()(k.from)
            ^ (hash<size_t>()(k.to) << 1)) >> 1);
        }
            };
}

class CFGBip {
public:
    CFGBip(size_t V);
    void addEdge(size_t from, size_t to, size_t branchLabels);
    size_t addDummyNode();
    Graph getCFGBipGraph();
    unordered_map<size_t, unordered_set<CFGBipEdge>> getEdgeMap();
private:
    unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap;
};

#endif
