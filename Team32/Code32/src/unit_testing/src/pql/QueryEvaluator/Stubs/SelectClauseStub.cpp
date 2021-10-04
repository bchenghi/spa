#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"

using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;
using pql::PkbAbstractor;

namespace qetest {
    class SelectClauseStub : public SelectClause {
    public:
        SelectClauseStub(vector<QueryDesignEntity> queryDesignEntities) : SelectClause(queryDesignEntities) {}
    };
}

