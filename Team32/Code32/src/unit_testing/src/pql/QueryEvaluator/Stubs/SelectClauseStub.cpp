#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"

using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;
using pql::PkbAbstractor;

namespace qetest {
    class SelectClauseStub : public SelectClause {
    public:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;

        SelectClauseStub(QueryDesignEntity queryDesignEntity) : SelectClause(queryDesignEntity) {}

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinations(PkbAbstractor *pkbAbstractor) {
            return results;
        }

        void addResults(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results) {
            this->results = results;
        }

    };
}

