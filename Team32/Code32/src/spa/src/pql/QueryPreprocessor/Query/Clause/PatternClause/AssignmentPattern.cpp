#include "AssignmentPattern.h"

using pql::AssignmentPattern;
using pql::FilterResult;
using pql::PkbAbstractor;

AssignmentPattern::AssignmentPattern(QueryArg queryDesignEntity, QueryArg variable, std::string subtreeStr) :
PatternClause(queryDesignEntity, variable, subtreeStr) {
    if ((queryDesignEntity.queryDesignEntity != nullptr &&
    queryDesignEntity.queryDesignEntity->designEntity != DesignEntity::Assign) ||
    (queryDesignEntity.argValue != nullptr &&
    queryDesignEntity.argValue->designEntity != DesignEntity::Assign)) {
        throw "Assignment Pattern Clause: First argument must be assignment";
    }

    if ((variable.queryDesignEntity != nullptr && variable.queryDesignEntity->designEntity != DesignEntity::Variable) ||
    (variable.argValue != nullptr && variable.argValue->designEntity != DesignEntity::Variable)) {
        throw "Assignment Pattern Clause: Second argument must be variable";
    }
}

FilterResult AssignmentPattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    return FilterResult({}, false);
}
