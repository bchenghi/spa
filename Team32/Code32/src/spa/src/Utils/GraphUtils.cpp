//
// Created by Jerry Lin on 3/11/21.
//

#include "GraphUtils.h"
#include "PKB/NextBipTable.h"
#include "PKB/NextTable.h"
#include "PKB/FollowTable.h"
#include "PKB/ParentTable.h"
#include "PKB/CallTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include <stdexcept>
#include <string>
#include <queue>
#include <vector>

void populateNextTable(Graph graph, string type, size_t stmtsSize) {
    for (int i = 0; i < stmtsSize; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j] == 1) {
                if (j < stmtsSize) {
                    if (type == "Next") {
                        NextTable::addNext(i + 1, j + 1);
                    } else {
                        NextBipTable::addNext(i + 1, j + 1);
                    }
                } else {
                    size_t dummyNode = j;
                    queue<size_t> frontier;
                    frontier.push(dummyNode);

                    while (!frontier.empty()) {
                        size_t next = frontier.front();
                        frontier.pop();

                        for (int k = 0; k < graph[next].size(); k++) {
                            if (graph[next][k] == 1) {
                                if (k < stmtsSize) {
                                    if (type == "Next") {
                                        NextTable::addNext(i + 1, k + 1);
                                    } else {
                                        NextBipTable::addNext(i + 1, k + 1);
                                    }
                                } else {
                                    frontier.push(k);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

Graph generateTransitiveClosureFor(Graph graph) {
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

Graph initGraph(size_t size) {
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

void setRelationWithGraph(Graph graph, const string &type, unordered_map<size_t, string> procIdRevMap) {
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

bool isCyclic(const Graph &graph) {
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

Graph generateFollowGraph(const unordered_map<size_t, size_t> &followTable) {
    Graph followGraph;

    size_t size = TypeToStmtNumTable::getLargestStmt();

    followGraph = initGraph(size);

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

Graph generateParentGraph(const unordered_map<size_t, unordered_set<size_t>> &parentTable) {
    Graph parentGraph;

    size_t size = TypeToStmtNumTable::getLargestStmt();

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

Graph generateCallGraph(const unordered_map<string, ListOfProcNames> &callTable,
                                    unordered_map<string, size_t> procIdMap) {
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
