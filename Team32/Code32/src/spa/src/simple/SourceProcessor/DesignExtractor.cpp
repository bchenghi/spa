#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "PKB/CallStmtTable.h"
#include "PKB/CallTable.h"
#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "PKB/UseTable.h"

using namespace std;

typedef vector<vector<size_t>> Graph; // Use adjacent list to represent graph

#include "DesignExtractor.h"


void simple::DesignExtractor::extractDesign() {
    // Get the transitive relationship for Follow and Parent
    unordered_map<size_t, size_t> followTable = FollowTable::getFollowMap();
    unordered_map<size_t, unordered_set<size_t>> parentTable = ParentTable::getParentMap();
    unordered_map<string, ListOfProcNames> callTable = CallTable::getCallMap();
    generateProcMap(ProcTable::getAllProcedure());

    // Generate the graph
    Graph followGraph = generateFollowGraph(followTable);
    Graph parentGraph = generateParentGraph(parentTable);
    Graph callGraph = generateCallGraph(callTable);

//    // Check whether call graph  is cyclic
    if (isCyclic(callGraph)) {
        throw logic_error("Have cyclic call in the source program");
    }

    // Build transitive relationship for graph
    Graph followTGraph = generateTransitiveClosureFor(followGraph);
    Graph parentTGraph = generateTransitiveClosureFor(parentGraph);
    Graph callTGraph = generateTransitiveClosureFor(callGraph);


    // Set the relationship to PKB
    setRelationWithGraph(followTGraph, "follow");
    setRelationWithGraph(parentTGraph, "parent");
    setRelationWithGraph(callTGraph, "call");

    // Extract use and modifies for container statement
    setUsesModifiesForProc();
    setUsesModifiesForStmt();
}

Graph simple::DesignExtractor::generateFollowGraph(const unordered_map<size_t, size_t>&  followTable) {
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

Graph simple::DesignExtractor::generateParentGraph(const unordered_map<size_t, unordered_set<size_t>>& parentTable) {
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

void simple::DesignExtractor::setRelationWithGraph(Graph graph, const string& type) {
    //NOTE: Be aware of the index for the adjacent list and statement list
    for (int i = 0; i < graph.size(); i++) {
        int from = i + 1;
        ListOfStmtNos list;
        unordered_set<string> procList;

        if (type != "call") {
            for (int j = 0; j < graph[i].size(); j++) {
                int to = j + 1;
                if (graph[i][j] == 1) {
                    list.insert(to);
                }
            }
        } else {
            for (int j = 0; j < graph[i].size(); j++) {
                int to = j;
                if (graph[i][j] == 1) {
                    procList.insert(procIdRevMap[to]);
                }
            }
        }

        if (type != "call" && list.empty()) {
            continue; // Continue when the list is empty to avoid dummy entry in map
        }

        if (type == "call" && procList.empty()) {
            continue;
        }

        if (type == "follow") {
            /*
            cout << "[Design Extractor] adding follow* relationship from: " << from << " to: ";
            for (auto num: list) {
                cout << num << ",";
            }
            cout << "\n";
             */

            FollowTable::addFollowStar(from, list);
        } else if (type == "parent") {
            /*
            cout << "[Design Extractor] adding children* relationship from: " << from << " to: ";
            for (auto num: list) {
                cout << num << ",";
            }
            cout << "\n";
             */

            ParentTable::addChildrenStar(from, list);
        } else if (type == "call") {
            ProcName from = procIdRevMap[i];
            for (const auto& proc:procList) {
                CallTable::addCallStar(from, proc);
            }
            continue;
        } else {
            throw logic_error("[Design Extractor] Invalid operation");
        }
    }

    for (int j = 0; j < graph.size(); j++) {
        int from = j + 1;
        ListOfStmtNos list;
        for (int i = 0; i < graph[j].size(); i++) {
            int to = i + 1;
            if (graph[i][j] == 1) {
                list.insert(to);
            }
        }

        if (list.empty()) {
            continue; // Continue when the list is empty to avoid dummy entry in map
        }

        if (type == "follow") {
            /*
            cout << "[Design Extractor] adding follow* by relationship from: " << from << " to: ";
            for (auto num: list) {
                cout << num << ",";
            }
            cout << "\n";
             */

            FollowTable::addFollowStarBy(from, list);
        } else if (type == "parent") {
            /*
            cout << "[Design Extractor] adding parent* relationship from: " << from << " to: ";
            for (auto num: list) {
                cout << num << ",";
            }
            cout << "\n";
             */

            ParentTable::addParentStar(from, list);
        } else if (type == "call") {
            return;
        } else {
            throw logic_error("[Design Extractor] Invalid operation");
        }
    }
}

void simple::DesignExtractor::setUsesModifiesForStmt() {
    unordered_map<size_t, size_t> parentInverseTable = ParentTable::getParentReverseMap();
    unordered_set<size_t> keys;

    // Generate key list
    for (auto kv: parentInverseTable) {
        keys.insert(kv.first);
    }

    // Set Uses and Modifies for call statement
    unordered_map<size_t, string> callStmtTable = CallStmtTable::getCallStmtToProcMap();

    for (const auto& kv: callStmtTable) {
        size_t stmtNum = kv.first;
        string procName = kv.second;
        unordered_set<VarName> stmtUsing = UseTable::getProcUse(procName);
        unordered_set<VarName> stmtModifying = ModifyTable::getProcModify(procName);

        for (const auto& useVar: stmtUsing) {
            UseTable::addStmtUse(stmtNum, useVar);
        }

        for (const auto& modifyVar: stmtModifying) {
            ModifyTable::addStmtModify(stmtNum, modifyVar);
        }
    }

    // Iterate through the statement number using parent inverse map
    for (unsigned long long stmtNum : keys) {
        size_t parent = parentInverseTable[stmtNum];
        unordered_set<VarName> usedVar = UseTable::getStmtUse(stmtNum);
        for (const auto& var: usedVar) {
            size_t tempParent = parent;
            while(tempParent != 0) { // Loop until the top level parent
//                cout << "[Design Extractor] Adding variable usage: " << tempParent << "," << var << "\n";
                UseTable::addStmtUse(tempParent, var);
                tempParent = parentInverseTable[tempParent];
            }
        }

        unordered_set<VarName> modifiedVar = ModifyTable::getStmtModify(stmtNum);

        for (const auto& var: modifiedVar) {
            size_t tempParent = parent;
            while(tempParent != 0) {
//                cout << "[Design Extractor] Adding variable modified: " << tempParent << "," << var << "\n";
                ModifyTable::addStmtModify(tempParent, var);
                tempParent = parentInverseTable[tempParent];
            }
        }
        // NOTE: Be aware that the insertion depends on the PKB data structure for Follow/Modifies table
    }
}


size_t simple::DesignExtractor::getStatementSize() {
    return TypeToStmtNumTable::getLargestStmt();
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

void simple::DesignExtractor::generateProcMap(ListOfProcNames procs) {
    int id = 0;
    for (const auto& proc: procs) {
        procIdMap[proc] = id;
        procIdRevMap[id] = proc;
        id++;
    }
}

Graph simple::DesignExtractor::generateCallGraph(const unordered_map<ProcName, ListOfProcNames>& callTable) {
    Graph callGraph;
    size_t size = ProcTable::getAllProcedure().size();
    callGraph = initGraph(int(size));

    for (auto entry: callTable) {
        size_t indexFrom = procIdMap[entry.first];
        vector<size_t> row = callGraph[indexFrom];
        row.reserve(size);

        for (auto procName: entry.second) {
            if (procIdMap.find(procName) == procIdMap.end()) {
                // proc not found
                throw logic_error("The program call procedure that does not exists");
            }

            row[procIdMap[procName]] = 1;
        }

        callGraph[indexFrom] = row;
    }


    return callGraph;
}

void simple::DesignExtractor::setUsesModifiesForProc() {
    unordered_map<string, unordered_set<string>> callInverseTable = CallTable::getCallStarReverseMap();
    unordered_set<string> keys;

    // Generate key list
    for (const auto& kv: callInverseTable) {
       keys.insert(kv.first);
    }

    // Iterate through the statement number using parent inverse map
    for (const auto& procName : keys) {
        unordered_set<string> parentProc = callInverseTable[procName];
        unordered_set<VarName> usedVar = UseTable::getProcUse(procName);
        unordered_set<VarName> modifiedVar = ModifyTable::getProcModify(procName);

        for (const auto& proc: parentProc) {
            for (const auto& var: usedVar) {
                UseTable::addProcUse(proc, var);
            }

            for (const auto& var: modifiedVar) {
                ModifyTable::addProcModify(proc, var);
            }
        }
        // NOTE: Be aware that the insertion depends on the PKB data structure for Follow/Modifies table
    }
}

bool simple::DesignExtractor::isCyclic(const Graph& graph) {
    size_t size = graph.size();

    vector<int> in(size, 0);

    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            if (graph[u][v] == 1) {
                in[v]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < size; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;

    vector<int> top_order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (int i = 0; i < size; i++) {
            if (graph[u][i] == 1) {
                if (--in[i] == 0) {
                    q.push(i);
                }
            }
        }
        count++;
    }

    if (count != size) {
        return true;
    } else {
        return false;
    }
}







