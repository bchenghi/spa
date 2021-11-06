#ifndef GUARD_PATTERN_CLAUSE_H
#define GUARD_PATTERN_CLAUSE_H

#include <string>
#include <utility>
#include <vector>

#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class PatternClause : public FilterClause {
    public:
        QueryArg designEntityArg;
        QueryArg variableArg;

        std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> result;
            result.push_back(&designEntityArg);
            result.push_back(&variableArg);
            return result;
        }

        virtual bool operator==(const PatternClause& other) const {
            if (designEntityArg == other.designEntityArg && variableArg == other.variableArg) {
                return true;
            }
            return false;
        }

        void setQueryArgs(std::vector<QueryArg> queryArgs) {
            if (queryArgs.size() != 2) {
                throw "SetQueryArg parameter length invalid";
            }
            designEntityArg = queryArgs[0];
            variableArg = queryArgs[1];
        }
        void free() {
            designEntityArg.free();
            variableArg.free();
        }
    protected:
        PatternClause(QueryArg designEntityArg, QueryArg variableArg)
            : designEntityArg(designEntityArg), variableArg(variableArg) {
            if (designEntityArg.getQueryDesignEntity() != nullptr && designEntityArg.getQueryDesignEntity() -> getAttributeType() != AttributeType::NONE) {
                if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Pattern clause arguments should not have attribute type");
            }
            if (variableArg.getQueryDesignEntity() != nullptr && variableArg.getQueryDesignEntity() -> getAttributeType() != AttributeType::NONE) {
                if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Pattern clause arguments should not have attribute type");
            }

            if (designEntityArg.getQueryDesignEntity() != nullptr) {
                shldReturnFirst = true;
            }
            if (variableArg.getQueryDesignEntity() != nullptr) {
                shldReturnSecond = true;
            }
        }
    };
}

#endif
