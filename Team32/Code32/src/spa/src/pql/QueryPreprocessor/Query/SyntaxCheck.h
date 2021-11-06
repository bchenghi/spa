#ifndef GUARD_SYNTAX_CHECK_FLAG_H
#define GUARD_SYNTAX_CHECK_FLAG_H
#include "QueryArg.h"

namespace pql {
    class SyntaxCheck {
    public:
        static bool isSyntaxCheck();
        static void setSyntaxCheckFlag(bool new_flag);
        static bool isEntRef(QueryArg queryArg);
        static bool isStmtRef(QueryArg queryArg);
    private:
        inline static bool flag;
    };
}

#endif
