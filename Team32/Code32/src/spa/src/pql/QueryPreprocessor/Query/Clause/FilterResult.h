#ifndef GUARD_FILTER_RESULT_H
#define GUARD_FILTER_RESULT_H

#include <vector>
#include <unordered_map>
#include <utility>
#include "../QueryArgValue.h"
#include "../QueryDesignEntity.h"

using std::vector;
using std::pair;
using std::unordered_map;

namespace pql {
    class FilterResult {
    private:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;

    public:
        bool addResult(vector<pair<QueryDesignEntity, QueryArgValue>> result);
        int getSize();
        vector<pair<QueryDesignEntity, QueryArgValue>> getEntitiesAndValuesAtIndex(int index);
    };
}


#endif //GUARD_FILTER_RESULT_H
