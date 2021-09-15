//
// Created by Jerry Lin on 8/9/21.
//

#ifndef GUARD_DESIGNEXTRACTOR_H
#define GUARD_DESIGNEXTRACTOR_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// NOTE: Parent inverse should be one-to-one mapping
typedef vector<vector<size_t>> Graph; // Use adjacent list to represent graph

namespace simple {
    class DesignExtractor {
    public:
        void extractDesign();
    private:
        Graph generateFollowGraph(unordered_map<size_t, size_t>  followTable);
        Graph generateParentGraph(unordered_map<size_t, unordered_set<size_t>> parentTable);
        Graph generateTransitiveClosureFor(Graph graph);
        void setRelationWithGraph(Graph graph, string type);
        void setUsesModifiesForStmt();
        int getStatementSize();
        Graph initGraph(int size);
    };
}


#endif
