#include "ModifiesClause.h"

using pql::FilterResult;
using pql::ModifiesClause;
using pql::PkbAbstractor;

ModifiesClause::ModifiesClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg){
    if (firstArg.isWildCard) {
        throw "Modifies Clause: First argument cannot be a wildcard";
    }

    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Constant)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::Variable ||
    firstArg.argValue->designEntity == DesignEntity::Constant))) {
        throw "Modifies Clause: First argument cannot be a variable or constant";
    }

    if ((secondArg.queryDesignEntity != nullptr && secondArg.queryDesignEntity->designEntity != DesignEntity::Variable) ||
    (secondArg.argValue != nullptr && secondArg.argValue->designEntity != DesignEntity::Variable)) {
        throw "Modifies Clause: Second argument must be a variable";
    }
}
FilterResult ModifiesClause::executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
    return FilterResult();
}
