#include "QueryProcessor/QueryPreprocessor/Query/Clause/SelectClause.h"

using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;

namespace pql {
    class SelectClauseStub : public SelectClause {
    public:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;

        SelectClauseStub(QueryDesignEntity queryDesignEntity) : SelectClause(queryDesignEntity) {}

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinations() {
            return results;
        }

        void addResults(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results) {
            for (int i = 0; i < results.size(); i++) {
                this->results = results;
            }
        }

    };
}

