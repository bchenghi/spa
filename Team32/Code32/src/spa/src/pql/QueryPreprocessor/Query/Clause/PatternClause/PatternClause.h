#ifndef GUARD_PATTERN_CLAUSE_H
#define GUARD_PATTERN_CLAUSE_H

#include <string>
#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class PatternClause : public FilterClause {
    public:
        QueryArg designEntityArg;
        QueryArg variableArg;
        std::string postFixStr;
        bool operator==(const PatternClause& other) const {
            if (designEntityArg == other.designEntityArg && variableArg == other.variableArg && postFixStr == other.postFixStr) {
                return true;
            }
            return false;
        }
        std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> result;
            result.push_back(&designEntityArg);
            result.push_back(&variableArg);
            return result;
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
        PatternClause(QueryArg designEntityArg, QueryArg variableArg, std::string postFixStr) : designEntityArg(designEntityArg),
        variableArg(variableArg), postFixStr(postFixStr){}
    };
}

#endif //GUARD_PATTERN_CLAUSE_H
