#ifndef GUARD_PATTERN_CLAUSE_H
#define GUARD_PATTERN_CLAUSE_H

#include <string>
#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class PatternClause : public FilterClause {
        QueryArg designEntity;
        QueryArg variable;
        std::string subtreeString;
        bool operator==(const PatternClause& other) const {
            if (designEntity == other.designEntity && variable == other.variable && subtreeString == other.subtreeString) {
                return true;
            }
            return false;
        }
        std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> result;
            result.push_back(&designEntity);
            result.push_back(&variable);
            return result;
        }

        void setQueryArgs(std::vector<QueryArg> queryArgs) {
            if (queryArgs.size() != 2) {
                throw "SetQueryArg parameter length invalid";
            }
            designEntity = queryArgs[0];
            variable = queryArgs[1];
        }
    };
}

#endif //GUARD_PATTERN_CLAUSE_H
