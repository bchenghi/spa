#ifndef GUARD_QUERY_PROCESSOR_MANAGER_H
#define GUARD_QUERY_PROCESSOR_MANAGER_H

#include <string>
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "pql/QueryPreprocessor/Preprocessor.h"


namespace pql {
    class QueryProcessorManager {
        QueryEvaluator queryEvaluator;
        Preprocessor queryPreprocessor;
    public:
        QueryProcessorManager();
        void executeQuery(std::string&);
    };
}


#endif //GUARD_QUERY_PROCESSOR_MANAGER_H
