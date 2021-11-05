#ifndef GUARD_QUERY_H
#define GUARD_QUERY_H

#include <vector>
#include "QueryDesignEntity.h"
#include "Clause/FilterClause.h"
#include "Clause/SelectClause.h"

namespace pql {
    class Query {
    public:
        Query(SelectClause* select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector);
        bool operator==(const Query& other) const;
        SelectClause* getSelectClause();
        std::vector<QueryDesignEntity> getQueryDesignEntities();
        std::vector<FilterClause*> getFilterClauses();
    private:
        SelectClause* select;
        std::vector<QueryDesignEntity> designEntitiesVector;
        std::vector<FilterClause*> filterClauseVector;
    };
}

#endif //GUARD_QUERY_H
