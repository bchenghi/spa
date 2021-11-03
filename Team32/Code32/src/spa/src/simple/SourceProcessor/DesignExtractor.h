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
#include "CFG.h"
#include "CFGBip.h"
#include "Utils/GraphUtils.h"
#include "pql/DesignEntity.h"

using namespace std;

// NOTE: Parent inverse should be one-to-one mapping
typedef vector<vector<size_t>> Graph; // Use adjacent list to represent graph

namespace simple {
    class DesignExtractor {
    public:
        void extractDesign();
    private:
        Graph cfg;
        CFGBip cfgBip = CFGBip(0,0);
        size_t stmtsSize;
        std::unordered_map<StmtNo, pql::DesignEntity> stmtsTypeMap;

        unordered_map<string, size_t> procIdMap;
        unordered_map<size_t, string> procIdRevMap;
        void setUsesModifiesForStmt();
        void generateProcMap(ListOfProcNames procs);
        void setUsesModifiesForProc();
        void initCFGBip();
        size_t generateCFGBip(Graph cfg, size_t startIndex, size_t stmtListSize, vector<size_t> branchList);
        size_t findFirstStmtForProc(string procName);
        size_t findStmtSizeForProc(string procName);
        size_t getNextStmtForCallStmt(size_t callStmtNo);
    };
}


#endif
