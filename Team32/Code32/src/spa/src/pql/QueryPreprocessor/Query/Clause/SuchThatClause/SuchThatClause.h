#ifndef GUARD_SUCH_THAT_CLAUSE
#define GUARD_SUCH_THAT_CLAUSE

#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class SuchThatClause : public FilterClause {
    public:
        QueryArg firstArg;
        QueryArg secondArg;
        bool operator==(const SuchThatClause& other) const {
            if (firstArg == other.firstArg && secondArg == other.secondArg) {
                return true;
            }
            return false;
        }
        std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> result;
            result.push_back(&firstArg);
            result.push_back(&secondArg);
            return result;
        }
        void setQueryArgs(std::vector<QueryArg> queryArgs) {
            if (queryArgs.size() != 2) {
                throw "SetQueryArg parameter length invalid";
            }
            firstArg = queryArgs[0];
            secondArg = queryArgs[1];
        }
        void free() {
            firstArg.free();
            secondArg.free();
        }
    protected:
        SuchThatClause(QueryArg firstArg, QueryArg secondArg) : firstArg(firstArg), secondArg(secondArg){
            if (firstArg.getQueryDesignEntity() != nullptr && firstArg.getQueryDesignEntity() -> getAttributeType() != AttributeType::NONE) {
                if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Such that clause arguments should not have attribute type");
            }
            if (secondArg.getQueryDesignEntity() != nullptr && secondArg.getQueryDesignEntity() -> getAttributeType() != AttributeType::NONE) {
                if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Such that clause arguments should not have attribute type");
            }

            if (firstArg.getQueryDesignEntity() != nullptr) {
                shldReturnFirst = true;
            }
            if (secondArg.getQueryDesignEntity() != nullptr) {
                shldReturnSecond = true;
            }
        }
    };
}

#endif
