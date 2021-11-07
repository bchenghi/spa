#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "PKB/CallStmtTable.h"
#include "PKB/CallTable.h"
#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "PKB/UseTable.h"
#include "PKB/CFGTable.h"
#include "PKB/CFGBipTable.h"
#include "Utils/GraphUtils.h"

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
    Graph callGraph = generateCallGraph(callTable, procIdMap);

    // Check whether call graph is cyclic
    if (isCyclic(callGraph)) {
        throw logic_error("Have cyclic call in the source program");
    }

    // Build transitive relationship for graph
    Graph followTGraph = generateTransitiveClosureFor(followGraph);
    Graph parentTGraph = generateTransitiveClosureFor(parentGraph);
    Graph callTGraph = generateTransitiveClosureFor(callGraph);


    // Set the relationship to PKB
    setRelationWithGraph(followTGraph, "follow", procIdRevMap);
    setRelationWithGraph(parentTGraph, "parent", procIdRevMap);
    setRelationWithGraph(callTGraph, "call", procIdRevMap);

    // Extract use and modifies for container statement
    setUsesModifiesForProc();
    setUsesModifiesForStmt();

    stmtsSize = TypeToStmtNumTable::getLargestStmt();
    cfg = CFGTable::getCFG();
    stmtsTypeMap = TypeToStmtNumTable::getStmtToTypeMap();

    if (stmtsSize < 50 && !cfg.empty()) {
        initCFGBip();
        generateCFGBip(cfg, 0, stmtsSize, 0);

        CFGBipTable::setCFGBip(cfgBip.getCFGBipGraph());
        CFGBipTable::setEdgeMap(cfgBip.getEdgeMap());
        populateNextTable(cfgBip.getCFGBipGraph(), "NextBip", stmtsSize);
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
                UseTable::addStmtUse(tempParent, var);
                tempParent = parentInverseTable[tempParent];
            }
        }

        unordered_set<VarName> modifiedVar = ModifyTable::getStmtModify(stmtNum);

        for (const auto& var: modifiedVar) {
            size_t tempParent = parent;
            while(tempParent != 0) {
                ModifyTable::addStmtModify(tempParent, var);
                tempParent = parentInverseTable[tempParent];
            }
        }
        // NOTE: Be aware that the insertion depends on the PKB data structure for Follow/Modifies table
    }
}

void simple::DesignExtractor::generateProcMap(ListOfProcNames procs) {
    int id = 0;
    for (const auto& proc: procs) {
        procIdMap[proc] = id;
        procIdRevMap[id] = proc;
        id++;
    }
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


void simple::DesignExtractor::initCFGBip() {
    size_t V = cfg.size();
    cfgBip = CFGBip(V);
}

size_t simple::DesignExtractor::generateCFGBip(Graph cfg, size_t startIndex, size_t stmtListSize, size_t branch) {
    size_t maxStmtNo = startIndex + 1;
    for (size_t i = startIndex; i < startIndex + stmtListSize; i++) {
        size_t currStmtNo = i + 1;

        if (stmtsTypeMap[currStmtNo] == pql::DesignEntity::CALL) {

            // Generate input for recursive call
            size_t newBranch = currStmtNo;
            size_t newStartStmtNo = findFirstStmtForProc(CallStmtTable::getProcCalled(currStmtNo));
            size_t targetProcStmtSize = findStmtSizeForProc(CallStmtTable::getProcCalled(currStmtNo));

            // Add edge between call and start of next procedure
            cfgBip.addEdge(currStmtNo, newStartStmtNo, newBranch);

            // Construct the CFGBip for from this branch
            size_t terminateStmtNo = generateCFGBip(cfg, newStartStmtNo - 1, targetProcStmtSize, newBranch);

            // Add edge between terminate node and next node after the call statement
            size_t nextNode = getNextStmtForCallStmt(currStmtNo);
            if (nextNode == -1) {
                // Case that the call statement is the last one in statement
                size_t dummyNode = cfgBip.addDummyNode();
                cfgBip.addEdge(terminateStmtNo, dummyNode, -newBranch);
            } else {
                cfgBip.addEdge(terminateStmtNo, nextNode, -newBranch);
            }
        } else {
            vector<size_t> adjList = cfg.at(i);

            if (i + 1 > maxStmtNo) {
                maxStmtNo = i + 1;
            }

            for (size_t j = 0; j < adjList.size(); j++) {
                size_t targetStmtNo = j + 1;
                if (adjList[j] == 1) {
                    if (targetStmtNo > maxStmtNo) {
                        maxStmtNo = targetStmtNo;
                    }
                    cfgBip.addEdge(currStmtNo, targetStmtNo, branch);
                }
            }
        }
    }

    return maxStmtNo;
}

size_t simple::DesignExtractor::findFirstStmtForProc(string procName) {
    ListOfStmtNos stmts = ProcTable::getProcStmtList(procName);
    return *std::min_element(stmts.begin(), stmts.end());
}

size_t simple::DesignExtractor::findStmtSizeForProc(string procName) {
    return ProcTable::getProcStmtList(procName).size();
}

size_t simple::DesignExtractor::getNextStmtForCallStmt(size_t callStmtNo) {
    size_t stmtIndex = callStmtNo - 1;
    vector<size_t> adjList = cfg.at(stmtIndex);

    for (int i = 0; i < adjList.size(); i++) {
        if (adjList.at(i) == 1) {
            return i + 1;
        }
    }

    return -1; // Last statement in procedure case
}




