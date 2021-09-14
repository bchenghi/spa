#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../../PKB/FollowTable.h"
#include "../../PKB/ParentTable.h"
#include "../../PKB/UseTable.h"
#include "../../PKB/ModifyTable.h"

using namespace std;

// TODO: Change when PKB API finished
// NOTE: Parent inverse should be one-to-one mapping
typedef unordered_map<size_t, size_t> ParentInverseTable;
typedef vector<vector<size_t>> Graph; // Use adjacent list to represent graph

#include "DesignExtractor.h"


void simple::DesignExtractor::extractDesign() {
    // Get the transitive relationship for Follow and Parent
    unordered_map<size_t, size_t> followTable = FollowTable::getFollowMap();
    unordered_map<size_t, unordered_set<size_t>> parentTable = ParentTable::getParentMap();

    // Generate the graph
    Graph followGraph = generateFollowGraph(followTable);
    Graph parentGraph = generateParentGraph(parentTable);

    // Build transitive relationship for graph
    Graph followTGraph = generateTransitiveClosureFor(followGraph);
    Graph parentTGraph = generateTransitiveClosureFor(parentGraph);

    // Set the relationship to PKB
    setRelationWithGraph(followTGraph, "follow");
    setRelationWithGraph(parentTGraph, "parent");

    // Extract use and modifies for container statement
    setUsesModifiesForStmt();
}

Graph simple::DesignExtractor::generateFollowGraph(unordered_map<size_t, size_t>  followTable) {
    Graph followGraph;

    int size = getStatementSize();
    followGraph = initGraph(size);

    auto graphIt = followGraph.begin();
    for (auto entry: followTable) {
        size_t indexFrom = entry.first - 1;
        size_t indexTo = entry.second - 1;
        vector<size_t> row = followGraph[indexFrom];

        for (int i = 0; i < size; i++) {
            if (i == indexTo) {
                row[i] = 1;
            }
        }

        followGraph[indexFrom] = row;
    }
    return followGraph;
}

Graph simple::DesignExtractor::generateParentGraph(unordered_map<size_t, unordered_set<size_t>> parentTable) {
    Graph parentGraph;
    int size = getStatementSize();
    parentGraph = initGraph(size);

    for (auto entry: parentTable) {
        size_t indexFrom = entry.first - 1;
        vector<size_t> row = parentGraph[indexFrom];
        row.reserve(size);

        for (int i = 0; i < size; i++) {
            if (entry.second.find(i + 1) != entry.second.end()) {
                row[i] = 1;
            } else {
                row[i] = 0;
            }
        }

        parentGraph[indexFrom] = row;
    }

    return parentGraph;
}

Graph simple::DesignExtractor::generateTransitiveClosureFor(Graph graph) {
    // Modified Floyd Warshall with a boolean reachable array
    size_t numV = graph.size();
    Graph reach;
    reach = initGraph(int(numV));

    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            reach[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                reach[i][j] = (reach[i][j] == 1) ||
                              ((reach[i][k] == 1) && reach[k][j] == 1) ? 1 : 0;
            }
        }
    }

    return reach;
}

void simple::DesignExtractor::setRelationWithGraph(Graph graph, string type) {
    //NOTE: Be aware of the index for the adjacent list and statement list
    for (int i = 0; i < graph.size(); i++) {
        int from = i + 1;
        LIST_OF_STMT_NO list;
        for (int j = 0; j < graph[i].size(); j++) {
            int to = j + 1;
            if (graph[i][j] == 1) {
                list.insert(to);
            }
        }

        if (type == "follow") {
            cout << "adding follow start relationship from: " << from << " to";
            for (auto num: list) {
                cout << num << ",";
            }
            FollowTable::addFollowStar(from, list);
        } else if (type == "parent") {
            ParentTable::addParentStar(from, list);
        } else {
            throw logic_error("Invalid operation");
        }
    }
}

void simple::DesignExtractor::setUsesModifiesForStmt() {
    unordered_map<size_t, size_t> parentInverseTable = ParentTable::getParentReverseMap();
    vector<size_t> keys;

    // Generate key list
    for (auto kv: parentInverseTable) {
        keys.push_back(kv.first);
    }

    // Iterate through the statement number using parent inverse map
    for (unsigned long long stmtNum : keys) {
        size_t parent = parentInverseTable[stmtNum];

        unordered_set<VAR_NAME> usedVar = UseTable::getStmtUse(stmtNum);

        for (const auto& var: usedVar) {
            UseTable::addStmtUse(parent, var);
        }

        unordered_set<VAR_NAME> modifiedVar = UseTable::getStmtUse(stmtNum);

        for (const auto& var: modifiedVar) {
            ModifyTable::addStmtModify(parent, var);
        }
        // NOTE: Be aware that the insertion depends on the PKB data structure for Follow/Modifies table
    }
}


int simple::DesignExtractor::getStatementSize() {
    unordered_map<size_t, size_t> followTable = FollowTable::getFollowMap();
    unordered_map<size_t, unordered_set<size_t>> parentTable = ParentTable::getParentMap();
    unordered_set<size_t> stmts;

    for (auto entry: followTable) {
        stmts.insert(entry.first);
        stmts.insert(entry.second);
    }

    for (auto entry: parentTable) {
        stmts.insert(entry.first);
        for (auto ele:entry.second) {
            stmts.insert(ele);
        }
    }

    return stmts.size();
}

Graph simple::DesignExtractor::initGraph(int size) {
    Graph graph;
    graph.reserve(size);

    for (int i = 0; i < size; i++) {
        vector<size_t> row;
        row.reserve(size);
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }
        graph.push_back(row);
    }

    return graph;
}


