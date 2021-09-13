#include "Preprocessor.h"
#include "PreprocessorHelper.h"
#include "../Tokenizer/Token.h"
#include "../Tokenizer/Tokenizer.h"


pql::Query pql::Preprocessor::preprocess(std::string query_text) {
	std::vector<pql::Token> token_list = pql::Tokenizer::tokenize(query_text);

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
	while (pql::PreprocessorHelper::parse_filters(token_list, filterClauseVector, designEntitiesVector));

	if (!token_list.empty()) {
		throw "Unable to parse all tokens.";
	}

	return pql::Query(select, designEntitiesVector, filterClauseVector);
}
