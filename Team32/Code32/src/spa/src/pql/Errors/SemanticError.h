#ifndef GUARD_SEMANTIC_ERROR_H
#define GUARD_SEMANTIC_ERROR_H

#include <string>
#include <exception>

using std::string;

namespace pql {
    class SemanticError : public std::exception {
    public:
        string errorMessage;
        SemanticError(string);
        const char* what();
    };
}


#endif
