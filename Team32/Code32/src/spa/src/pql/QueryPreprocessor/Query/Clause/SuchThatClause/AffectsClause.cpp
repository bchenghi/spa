#include "AffectsClause.h"

using pql::AffectsClause;

AffectsClause::AffectsClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if ((firstArg.queryDesignEntity != nullptr &&
    firstArg.queryDesignEntity->designEntity != DesignEntity::ASSIGN) ||
    (firstArg.argValue != nullptr &&
    firstArg.argValue->designEntity == DesignEntity::STMT)) {
        throw SemanticError("Affects Clause: First argument must be assignment");
    }

    if ((secondArg.queryDesignEntity != nullptr &&
    secondArg.queryDesignEntity->designEntity != DesignEntity::ASSIGN) ||
    (secondArg.argValue != nullptr &&
    secondArg.argValue->designEntity == DesignEntity::STMT)) {
        throw SemanticError("Affects Clause: Second argument must be assignment");
    }

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}
