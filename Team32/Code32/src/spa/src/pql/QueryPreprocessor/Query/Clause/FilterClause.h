#ifndef GUARD_FILTER_CLAUSE_H
#define GUARD_FILTER_CLAUSE_H

#include <vector>
#include "ClauseType.h"
#include "../QueryArg.h"
#include "../../../PkbAbstractor/PkbAbstractor.h"
#include "FilterResult.h"
#include "pql/Errors/SemanticError.h"
#include "../SyntaxCheck.h"

namespace pql {
    class FilterClause {
    public:
        virtual FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
            return FilterResult({}, false);
        };
        virtual std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> v = {};
            return v;
        };
        virtual ClauseType getClauseType() {
            return ClauseType::NONE;
        }

        virtual void free() {};

        bool getShldReturnFirst() {
            return shldReturnFirst;
        }

        bool getShldReturnSecond() {
            return shldReturnSecond;
        }

        void setShldReturnFirst(bool shldReturnFirst) {
            this->shldReturnFirst = shldReturnFirst;
        }

        void setShldReturnSecond(bool shldReturnSecond) {
            this->shldReturnSecond = shldReturnSecond;
        }

    protected:
        // If the argument is a synonym, should return their valid values in executePKBAbsQuery.
        // Set to true in constructors.
        bool shldReturnFirst = false;
        bool shldReturnSecond = false;
        virtual bool argIsValid(QueryArg) {
            return true;
        };
    };
}

#endif
