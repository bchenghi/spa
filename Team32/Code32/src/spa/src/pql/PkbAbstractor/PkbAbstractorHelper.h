#ifndef GUARD_PKB_ABSTRACTOR_HELPER_H
#define GUARD_PKB_ABSTRACTOR_HELPER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <list>
#include <utility>
#include <algorithm>
#include "../src/pql/DesignEntity.h"
#include "../src/pql/AttributeType.h"

typedef size_t StmtNum;
typedef size_t ProcLine;
typedef std::string VarName;
typedef std::string ProcName;
typedef std::string Value;
typedef std::vector<std::string> PostFixExpression;
typedef std::vector<std::vector<size_t>> Graph;

using std::string;
using std::list;
using std::pair;
using std::unordered_set;
using std::unordered_map;

namespace pql {
    class PkbAbstractorHelper {
    public:
        static bool isNum(const std::string&);
        static Graph initGraph(int);
        static Graph getGraph(Value);
        static void addGraph(Value, Graph);
        static void clearGraphs();
    private:
        static std::unordered_map<Value, Graph> graphsMap;
//>>>>>>> origin/refactorCode
    };
}

#endif //GUARD_PKB_ABSTRACTOR_HELPER_H
