#include "NextClause.h"

using pql::NextClause;

NextClause::NextClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::VARIABLE ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::CONSTANT ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::PROCEDURE)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::VARIABLE ||
    firstArg.argValue->designEntity == DesignEntity::CONSTANT ||
    firstArg.argValue->designEntity == DesignEntity::PROCEDURE))) {
        throw SemanticError("Next Clause: First argument cannot be a variable, constant or procedure");
    }

    if ((secondArg.queryDesignEntity != nullptr &&
    (secondArg.queryDesignEntity->designEntity == DesignEntity::VARIABLE ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::CONSTANT ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::PROCEDURE)) ||
    (secondArg.argValue != nullptr &&
    (secondArg.argValue->designEntity == DesignEntity::VARIABLE ||
    secondArg.argValue->designEntity == DesignEntity::CONSTANT ||
    secondArg.argValue->designEntity == DesignEntity::PROCEDURE))) {
        throw SemanticError("Next Clause: Second argument cannot be a variable, constant or procedure");
    }

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}