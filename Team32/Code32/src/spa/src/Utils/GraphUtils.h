//
// Created by Jerry Lin on 3/11/21.
//

#ifndef GUARD_GRAPHUTILS_H
#define GUARD_GRAPHUTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "PKB/TypePreDefine.h"
using namespace std;

typedef vector<vector<size_t>> Graph;


void populateNextTable(Graph graph, string type, size_t stmtsSize);
Graph generateTransitiveClosureFor(Graph graph);
void setRelationWithGraph(Graph graph, const string& type, unordered_map<size_t, string> procIdRevMap);
bool isCyclic(const Graph& graph);
Graph generateFollowGraph(const unordered_map<size_t, size_t>&  followTable);
Graph generateParentGraph(const unordered_map<size_t, unordered_set<size_t>>& parentTable);
Graph generateCallGraph(const unordered_map<string, ListOfProcNames>& callTable,
                                   unordered_map<string, size_t> procIdMap);
Graph initGraph(size_t size);



#endif //AUTOTESTER_GRAPHUTILS_H
