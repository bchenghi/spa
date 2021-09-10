#ifndef GUARD_PKB_ABSTRACTOR_HELPER_H
#define GUARD_PKB_ABSTRACTOR_HELPER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <utility>
#include <algorithm>
#include "../src/pql/DesignEntity.h"

typedef int StmtNum;
typedef std::string VarName;
typedef std::string Value;

using std::string;
using std::list;
using std::pair;
using std::unordered_set;

typedef string VAR_NAME;
typedef string PROC_NAME;

namespace pql {
    class PkbAbstractorHelper {
    public:
        static bool isNum(const std::string&);

        static list<pair<string, unordered_set<VAR_NAME>>> usesDesignEntityHelper(DesignEntity, VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesAssignHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesPrintHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesWhileHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesIfHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesProcHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> usesStmtNumHelper(StmtNum, VarName);
        static list<pair<string, unordered_set<PROC_NAME>>> usesProcNameHelper(string, VarName);

        static list<pair<string, unordered_set<VAR_NAME>>> modifiesDesignEntityHelper(DesignEntity, VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesAssignHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesReadHelper(VarName varName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesWhileHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesIfHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesProcHelper(VarName);
        static list<pair<string, unordered_set<VAR_NAME>>> modifiesStmtNumHelper(StmtNum, VarName);
        static list<pair<string, unordered_set<PROC_NAME>>> modifiesProcNameHelper(string, VarName);

    };
}

#endif //AUTOTESTER_PKB_ABSTRACTOR_HELPER_H
