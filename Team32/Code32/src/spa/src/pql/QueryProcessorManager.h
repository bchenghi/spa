#ifndef GUARD_QUERY_PROCESSOR_MANAGER_H
#define GUARD_QUERY_PROCESSOR_MANAGER_H

#include <string>
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "pql/QueryPreprocessor/Preprocessor.h"

namespace pql {
    class QueryProcessorManager {
        QueryEvaluator queryEvaluator;
        Preprocessor queryPreprocessor;
        QueryResultProjector queryResultProjector;
    public:
        bool isOptimisationOn = true;
        QueryProcessorManager();
        void setOptimisation(bool);
        set<string> executeQuery(std::string);
    };
}

#endif
