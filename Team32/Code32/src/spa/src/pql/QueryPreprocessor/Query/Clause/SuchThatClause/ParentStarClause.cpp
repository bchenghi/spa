#include "ParentStarClause.h"

using pql::FilterResult;
using pql::ParentStarClause;
using pql::PkbAbstractor;

ParentStarClause::ParentStarClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Constant ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Procedure)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::Variable ||
    firstArg.argValue->designEntity == DesignEntity::Constant||
    firstArg.argValue->designEntity == DesignEntity::Procedure))) {
        throw "Parent Star Clause: First argument cannot be a variable, constant or procedure";
    }
    if ((secondArg.queryDesignEntity != nullptr &&
    (secondArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::Constant ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::Procedure)) ||
    (secondArg.argValue != nullptr &&
    (secondArg.argValue->designEntity == DesignEntity::Variable ||
    secondArg.argValue->designEntity == DesignEntity::Constant||
    secondArg.argValue->designEntity == DesignEntity::Procedure))) {
        throw "Parent Star Clause: Second argument cannot be a variable, constant or procedure";
    }
}

FilterResult ParentStarClause::executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
    return FilterResult();
}