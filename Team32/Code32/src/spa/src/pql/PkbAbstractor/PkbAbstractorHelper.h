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

typedef size_t StmtNum;
typedef std::string VarName;
typedef std::string Value;

using std::string;
using std::list;
using std::pair;
using std::unordered_set;

typedef string VarName;
typedef string ProcName;

namespace pql {
    class PkbAbstractorHelper {
    public:
        static bool isNum(const std::string&);

        static list<pair<string, unordered_set<VarName>>> usesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesPrintHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> usesProcNameHelper(const string&, const VarName&);

        static list<pair<string, unordered_set<VarName>>> modifiesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesReadHelper(const VarName& varName);
        static list<pair<string, unordered_set<VarName>>> modifiesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> modifiesProcNameHelper(const string&, const VarName&);

    };
}

#endif //AUTOTESTER_PKB_ABSTRACTOR_HELPER_H
