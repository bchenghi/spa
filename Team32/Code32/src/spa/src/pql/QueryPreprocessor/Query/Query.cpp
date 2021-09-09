#include "Query.h"
#include <unordered_set>

using std::unordered_set;
using pql::FilterClause;
using pql::Query;
using pql::QueryDesignEntity;
using pql::SelectClause;

Query::Query(SelectClause* select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector)
: select(select), designEntitiesVector(designEntitiesVector), filterClauseVector(filterClauseVector) {
    unordered_set<QueryDesignEntity> designEntitiesSet(designEntitiesVector.begin(), designEntitiesVector.end());

    if (designEntitiesSet.find(select->queryDesignEntity) == designEntitiesSet.end()) {
        throw "Query: Selected entity is not declared";
    }

    for (FilterClause* filterClause : filterClauseVector) {
        vector<QueryArg*> queryArgs = filterClause->getQueryArgs();
        for (QueryArg* queryArg : queryArgs) {
            if (queryArg->queryDesignEntity != nullptr && designEntitiesSet.find(*queryArg->queryDesignEntity) == designEntitiesSet.end()) {
                throw "Query: Query argument in clause is not declared";
            }
        }
    }
}
