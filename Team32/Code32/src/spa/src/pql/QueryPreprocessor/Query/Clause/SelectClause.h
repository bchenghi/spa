#ifndef GUARD_SELECT_CLAUSE_H
#define GUARD_SELECT_CLAUSE_H

#include <utility>
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
        vector<QueryDesignEntity> queryDesignEntities;
        SelectClause(vector<QueryDesignEntity> queryDesignEntities) : queryDesignEntities(std::move(queryDesignEntities)) {}
        virtual vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinations(PkbAbstractor *pkbAbstractor);
        bool operator==(const SelectClause& other) const;
    private:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromStmtLst(const ListOfStmtNos&);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromValues(const vector<std::string>&);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinationsFromLargestInt(int);
    };
}


#endif //GUARD_SELECT_CLAUSE_H
