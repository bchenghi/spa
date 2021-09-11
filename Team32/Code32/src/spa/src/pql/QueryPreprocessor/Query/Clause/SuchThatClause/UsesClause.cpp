#include "UsesClause.h"

using pql::FilterResult;
using pql::PkbAbstractor;
using pql::UsesClause;

UsesClause::UsesClause(QueryArg queryArg, QueryArg queryArg1) : SuchThatClause(queryArg, queryArg1) {
    if (firstArg.isWildCard) {
        throw "Uses Clause: First argument cannot be a wildcard";
    }

    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Constant)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::Variable ||
    firstArg.argValue->designEntity == DesignEntity::Constant))) {
        throw "Uses Clause: First argument cannot be a variable or constant";
    }

    if ((secondArg.queryDesignEntity != nullptr && secondArg.queryDesignEntity->designEntity != DesignEntity::Variable) ||
    (secondArg.argValue != nullptr && secondArg.argValue->designEntity != DesignEntity::Variable)) {
        throw "Uses Clause: Second argument must be a variable";
    }
}

FilterResult UsesClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {

    return FilterResult({}, false);
}
