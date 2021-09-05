#ifndef GUARD_PKB_ABSTRACTOR_HELPER_H
#define GUARD_PKB_ABSTRACTOR_HELPER_H

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include "../src/pql/DesignEntity.h"

typedef int StmtNum;
typedef std::string VarName;
typedef std::string Value;

using std::string;
using std::list;
using std::pair;

namespace pql {
    class PkbAbstractorHelper {
    public:
        static bool isNum(const std::string&);

        static list<pair<string, list<string>>> usesDesignEntityHelper(DesignEntity, VarName);
        static list<pair<string, list<string>>> usesAssignHelper(VarName);
        static list<pair<string, list<string>>> usesPrintHelper(VarName);
        static list<pair<string, list<string>>> usesWhileHelper(VarName);
        static list<pair<string, list<string>>> usesIfHelper(VarName);
        static list<pair<string, list<string>>> usesProcHelper(VarName);
        static list<pair<string, list<string>>> usesStmtNumHelper(StmtNum, VarName);
        static list<pair<string, list<string>>> usesProcNameHelper(string, VarName);

        static list<pair<string, list<string>>> modifiesDesignEntityHelper(DesignEntity, VarName);
        static list<pair<string, list<string>>> modifiesAssignHelper(VarName);
        static list<pair<string, list<string>>> modifiesReadHelper(VarName varName);
        static list<pair<string, list<string>>> modifiesWhileHelper(VarName);
        static list<pair<string, list<string>>> modifiesIfHelper(VarName);
        static list<pair<string, list<string>>> modifiesProcHelper(VarName);
        static list<pair<string, list<string>>> modifiesStmtNumHelper(StmtNum, VarName);
        static list<pair<string, list<string>>> modifiesProcNameHelper(string, VarName);

    };
}

#endif //AUTOTESTER_PKB_ABSTRACTOR_HELPER_H
