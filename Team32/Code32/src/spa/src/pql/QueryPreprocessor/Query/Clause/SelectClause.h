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
        vector<QueryDesignEntity> getSelectedEntities();
        SelectClause(vector<QueryDesignEntity> queryDesignEntities) : queryDesignEntities(std::move(queryDesignEntities)) {}
        bool operator==(const SelectClause& other) const;
    private:
        vector<QueryDesignEntity> queryDesignEntities;
    };
}


#endif //GUARD_SELECT_CLAUSE_H
