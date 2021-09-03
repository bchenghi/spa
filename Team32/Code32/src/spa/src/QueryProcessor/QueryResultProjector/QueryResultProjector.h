#ifndef GUARD_QUERY_RESULT_PROJECTOR_H
#define GUARD_QUERY_RESULT_PROJECTOR_H

#include <vector>
#include <string>

namespace pql{
    class QueryResultProjector {
    public:
        std::string outputResult(std::vector<std::string> results);
    };
}


#endif //GUARD_QUERY_RESULT_PROJECTOR_H
