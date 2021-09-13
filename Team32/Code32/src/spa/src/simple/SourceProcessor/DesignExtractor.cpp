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

#include "DesignExtractor.h"


void simple::DesignExtractor::extractDesign() {
    // Get the transitive relationship for Follow and Parent
    //TODO: Get Table from PKB
    FollowTable followTable;
    ParentTable parentTable;

    // Generate the graph
    Graph followGraph = generateFollowGraph(followTable);
    Graph parentGraph = generateParentGraph(parentTable);

    // Build transitive relationship for graph
    Graph followTGraph = generateTransitiveClosureFor(followGraph);
    Graph parentTGraph = generateTransitiveClosureFor(parentGraph);

    // Set the relationship to PKB
    setRelationWithGraph(followTGraph);
    setRelationWithGraph(parentTGraph);

    // Extract use and modifies for container statement
}

Graph simple::DesignExtractor::generateFollowGraph(FollowTable followTable) {
    //TODO: Add when PKB specification done, might not need this method
    Graph followGraph;
    return followGraph;
}

Graph simple::DesignExtractor::generateParentGraph(ParentTable parentTable) {
    //TODO: Add when PKB specification done, might not need this method
    Graph parentGraph;
    return parentGraph;
}

Graph simple::DesignExtractor::generateTransitiveClosureFor(Graph graph) {
    // Modified Floyd Warshall with a boolean reachable array
    size_t numV = graph.size();
    Graph reach;

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            for (int k = 0; k < numV; k++) {
                reach[j][k] = (graph[j][k] == 1) ||
                              ((reach[j][i] == 1) && reach[i][k] == 1) ? 1 : 0;
            }
        }
    }

    return reach;
}

void simple::DesignExtractor::setRelationWithGraph(Graph graph) {
    // TODO: Set the transitive relation to PKB
    //NOTE: Be aware of the index for the adjacent list and statement list
}

// TODO: Do not need this if PKB store the inversed table
ParentInverseTable simple::DesignExtractor::generateParentInverse(ParentTable parentTable) {
    ParentInverseTable parentInverseTable;
    return parentInverseTable;
}

void simple::DesignExtractor::setUsesModifiesForContainer(UsesTable usesTable, ModifiesTable modifiesTable) {

    ParentInverseTable parentInverseTable;
    vector<size_t> keys;

    // Generate key list
    for (auto kv: parentInverseTable) {
        keys.push_back(kv.first);
    }

    // Iterate through the statement number using parent inverse map
    for (int i = 0; i < keys.size(); i++) {
        size_t stmtNum = keys[i];
        size_t parent = parentInverseTable[stmtNum];

        // TODO: Check what's used in this statement (Require PKB API)
        // TODO: Insert uses/modifies for it's parent (Require PKB API)
        // NOTE: Be aware that the insertion depends on the PKB data structure for Follow/Modifies table
    }
}
