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
        unordered_map<string, size_t> procIdMap;
        unordered_map<size_t, string> procIdRevMap;
        Graph generateFollowGraph(const unordered_map<size_t, size_t>&  followTable);
        Graph generateParentGraph(const unordered_map<size_t, unordered_set<size_t>>& parentTable);
        Graph generateTransitiveClosureFor(Graph graph);
        void setRelationWithGraph(Graph graph, const string& type);
        void setUsesModifiesForStmt();
        size_t getStatementSize();
        Graph initGraph(int size);
        Graph generateCallGraph(const unordered_map<ProcName, ListOfProcNames>& callTable);
        void generateProcMap(ListOfProcNames procs);
        void setUsesModifiesForProc();
        bool isCyclic(const Graph& graph);
    };
}


#endif
