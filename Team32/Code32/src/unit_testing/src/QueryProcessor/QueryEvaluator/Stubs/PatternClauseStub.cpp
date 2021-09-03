#include "QueryProcessor/QueryPreprocessor/Query/FilterClause/PatternClause/PatternClause.h"


using std::vector;
using std::pair;
using pql::PatternClause;
using pql::QueryDesignEntity;
using pql::DesignEntity;
using pql::FilterResult;
using pql::PkbAbstractor;
using pql::QueryArgValue;

class PatternClauseStub : public PatternClause {
private:
    FilterResult f;
public:
    FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
        return f;
    };
    void addResults(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results) {
        for (int i = 0; i < results.size(); i++) {
            f.addResult(results[i]);
        }
    }
};
