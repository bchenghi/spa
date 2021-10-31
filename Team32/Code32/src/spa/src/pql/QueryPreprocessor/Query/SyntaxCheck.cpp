#include "SyntaxCheck.h"

namespace pql {
    bool SyntaxCheck::isSyntaxCheck() {
        return flag;
    }

    void SyntaxCheck::setSyntaxCheckFlag(bool new_flag) {
        flag = new_flag;
    }

    bool SyntaxCheck::isEntRef(QueryArg queryArg) {
        if (queryArg.isWildCard || queryArg.queryDesignEntity != nullptr) {
            return true;
        }
        if (queryArg.argValue != nullptr && queryArg.argValue->designEntity == DesignEntity::VARIABLE) {
            return true;
        }
        return false;
    }

    bool SyntaxCheck::isStmtRef(QueryArg queryArg) {
        if (queryArg.isWildCard || queryArg.queryDesignEntity != nullptr) {
            return true;
        }
        if (queryArg.argValue != nullptr && queryArg.argValue->designEntity == DesignEntity::STMT) {
            return true;
        }
        return false;
    }
}