#include "SelectClause.h"

using std::pair;
using std::vector;
using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;

// Returns all combinations of values of the entities in the select clauses
vector<vector<pair<QueryDesignEntity, QueryArgValue>>> SelectClause::getAllEntityCombinations() {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> v;
    return v;
}
