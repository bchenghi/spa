#include "Preprocessor.h"
#include "PreprocessorHelper.h"

#include <cassert>

bool pql::Preprocessor::checkBooleanSelect(std::string queryText) {
    return queryText.find("Select BOOLEAN") != std::string::npos;
}

bool syntax_check(std::string queryText) {
    pql::SyntaxCheck::setSyntaxCheckFlag(true);
    std::vector<pql::Token> token_list = pql::Tokenizer::tokenize(queryText);

    pql::SelectClause* select = nullptr;
    std::vector<pql::QueryDesignEntity> designEntitiesVector;
    std::vector<pql::FilterClause*> filterClauseVector;
    std::vector<pql::QueryArg> queryArgs;
    try {
        // Parse declarations
        while (pql::PreprocessorHelper::parse_design_entity(token_list, designEntitiesVector));

        // Parse select clause
        if (!pql::PreprocessorHelper::parse_select_clause(token_list, select, designEntitiesVector)) {
            throw "Error parsing select clause";
        }

        // Parse filters
        std::string last_clause = "";
        while (pql::PreprocessorHelper::parse_filters(token_list, filterClauseVector, designEntitiesVector, last_clause, queryArgs));

        pql::PreprocessorHelper::free_pointers(select, filterClauseVector, queryArgs);
        
        if (!token_list.empty()) {
            return false;
        }
        return true;
    } catch (std::exception &ex) {
        pql::PreprocessorHelper::free_pointers(select, filterClauseVector, queryArgs);
        throw;
    }
}

pql::Query pql::Preprocessor::preprocess(std::string queryText) {
    if (!syntax_check(queryText)) {
        throw "Syntax error found.";
    }

    pql::SyntaxCheck::setSyntaxCheckFlag(false);
    std::vector<pql::Token> token_list = pql::Tokenizer::tokenize(queryText);

    pql::SelectClause* select = nullptr;
    std::vector<pql::QueryDesignEntity> designEntitiesVector;
    std::vector<pql::FilterClause*> filterClauseVector;
    std::vector<QueryArg> queryArgs;
    try {
        // Parse declarations
        while (pql::PreprocessorHelper::parse_design_entity(token_list, designEntitiesVector));

        // Parse select clause
        assert(pql::PreprocessorHelper::parse_select_clause(token_list, select, designEntitiesVector));

        // Parse filters
        std::string last_clause = "";
        while (pql::PreprocessorHelper::parse_filters(token_list, filterClauseVector, designEntitiesVector, last_clause, queryArgs));

        assert(token_list.empty());

        return pql::Query(select, designEntitiesVector, filterClauseVector);
    } catch (std::exception &ex) {
        pql::PreprocessorHelper::free_pointers(select, filterClauseVector, queryArgs);
        throw;
    }
}
