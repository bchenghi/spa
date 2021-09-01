#ifndef GUARD_FILTER_RESULT_H
#define GUARD_FILTER_RESULT_H

#include <vector>
#include <utility>
#include "../QueryArgValue.h"
#include "../QueryDesignEntity.h"

namespace pql {
    class FilterResult {
    private:
        std::vector<std::pair<QueryDesignEntity, QueryArgValue>> results;

    public:
        bool addResult(QueryDesignEntity queryDesignEntity, QueryArgValue value);
        int getSize();
        std::pair<QueryDesignEntity, QueryArgValue> getEntityValueAtIndex(int index);
    };
}


#endif //GUARD_FILTER_RESULT_H
