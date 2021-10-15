#include "Preprocessor.h"
#include "PreprocessorHelper.h"
#include "../Tokenizer/Token.h"
#include "../Tokenizer/Tokenizer.h"

bool pql::Preprocessor::checkBooleanSelect(std::string queryText) {
    return queryText.find("Select BOOLEAN") != std::string::npos;
}

pql::Query pql::Preprocessor::preprocess(std::string queryText) {
    std::vector<pql::Token> token_list = pql::Tokenizer::tokenize(queryText);

    pql::SelectClause* select;
    std::vector<pql::QueryDesignEntity> designEntitiesVector;
    std::vector<pql::FilterClause*> filterClauseVector;

    // Parse declarations
    while (pql::PreprocessorHelper::parse_design_entity(token_list, designEntitiesVector));

    // Parse select clause
    if (!pql::PreprocessorHelper::parse_select_clause(token_list, select, designEntitiesVector)) {
        throw "Cannot parse select clause.";
    }

    // Parse filters
    std::string last_clause = "";
    while (pql::PreprocessorHelper::parse_filters(token_list, filterClauseVector, designEntitiesVector, last_clause));

    if (!token_list.empty()) {
        throw "Unable to parse all tokens.";
    }

    return pql::Query(select, designEntitiesVector, filterClauseVector);
}
