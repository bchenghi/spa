#include "SyntaxCheck.h"

namespace pql {
    bool SyntaxCheck::isSyntaxCheck() {
        return flag;
    }

    void SyntaxCheck::setSyntaxCheckFlag(bool new_flag) {
        flag = new_flag;
    }

    bool SyntaxCheck::isEntRef(QueryArg queryArg) {
        if (queryArg.isWildCardArg() || queryArg.getQueryDesignEntity() != nullptr) {
            return true;
        }
        if (queryArg.getQueryArgValue() != nullptr && queryArg.getQueryArgValue()->getDesignEntity() == DesignEntity::VARIABLE) {
            return true;
        }
        return false;
    }

    bool SyntaxCheck::isStmtRef(QueryArg queryArg) {
        if (queryArg.isWildCardArg() || queryArg.getQueryDesignEntity() != nullptr) {
            return true;
        }
        if (queryArg.getQueryArgValue() != nullptr && queryArg.getQueryArgValue()->getDesignEntity() == DesignEntity::STMT) {
            return true;
        }
        return false;
    }
}