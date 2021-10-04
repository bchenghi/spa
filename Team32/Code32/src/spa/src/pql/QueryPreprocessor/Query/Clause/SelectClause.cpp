#include "SelectClause.h"

using std::pair;
using std::vector;
using pql::SelectClause;
using pql::QueryDesignEntity;
using pql::QueryArgValue;

bool SelectClause::operator==(const SelectClause& other) const {
    for (int i = 0; i < queryDesignEntities.size(); i++) {
        if (!(queryDesignEntities[i] == other.queryDesignEntities[i])) {
            return false;
        }
    }
    return true;
};
