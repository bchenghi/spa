//
// Created by Jerry Lin on 8/9/21.
//

#ifndef GUARD_DESIGNEXTRACTOR_H
#define GURAD_DESIGNEXTRACTOR_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// TODO: Change when PKB API finished
// NOTE: Parent inverse should be one-to-one mapping
typedef unordered_map<size_t, size_t> FollowTable, ParentInverseTable;
typedef unordered_map<size_t, vector<size_t>> ParentTable;
typedef unordered_map<size_t, string> UsesTable, ModifiesTable;
typedef vector<vector<size_t>> Graph; // Use adjacent list to represent graph

namespace simple {
    class DesignExtractor {
    public:
        void extractDesign();
    private:
        Graph generateFollowGraph(FollowTable followTable);
        Graph generateParentGraph(ParentTable parentTable);
        Graph generateTransitiveClosureFor(Graph graph);
        void setRelationWithGraph(Graph graph);
        void setUsesModifiesForContainer(UsesTable usesTable, ModifiesTable modifiesTable);

        ParentInverseTable generateParentInverse(ParentTable parentTable);
    };
}


#endif
