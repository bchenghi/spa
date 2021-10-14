#include "SemanticError.h"

using pql::SemanticError;

SemanticError::SemanticError(string errorMessage) : errorMessage(errorMessage) {}

const char* SemanticError::what() {
    return errorMessage.c_str();
};
