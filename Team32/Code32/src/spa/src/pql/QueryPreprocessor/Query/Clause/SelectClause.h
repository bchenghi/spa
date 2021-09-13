#ifndef GUARD_SELECT_CLAUSE_H
#define GUARD_SELECT_CLAUSE_H

#include <vector>
#include <utility>
#include "../QueryDesignEntity.h"
#include "../QueryArgValue.h"
#include "../../../PkbAbstractor/PkbAbstractor.h"

using std::pair;
using std::vector;

namespace pql {
    class SelectClause {
    public:
        QueryDesignEntity queryDesignEntity;
        SelectClause(QueryDesignEntity queryDesignEntity) : queryDesignEntity(queryDesignEntity) {}
        virtual vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinations(PkbAbstractor *pkbAbstractor);
    private:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromStmtLst(LIST_OF_STMT_NO);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromValues(vector<std::string>);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromLargestInt(int);
    };
}


#endif //GUARD_SELECT_CLAUSE_H
