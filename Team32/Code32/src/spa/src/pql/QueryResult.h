#ifndef GUARD_QUERY_RESULT_H
#define GUARD_QUERY_RESULT_H

#include <string>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::set;

namespace pql {
    class QueryResult {
    public:
        set<vector<string>> valueResult;
        bool booleanResult;
        bool isBooleanSelect;
        QueryResult(set<vector<string>> valueResult);
        QueryResult(bool booleanResult);
        bool operator==(const QueryResult& other) const {
            return valueResult == other.valueResult && booleanResult == other.booleanResult &&
            isBooleanSelect == other.isBooleanSelect;
        }
    };
}


#endif
