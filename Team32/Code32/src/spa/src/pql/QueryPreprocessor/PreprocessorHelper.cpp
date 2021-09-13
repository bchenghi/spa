#include "PreprocessorHelper.h"
#include "Query/Clause/SuchThatClause/SuchThatClause.h"
#include "Query/Clause/SuchThatClause/FollowsClause.h"
#include "Query/Clause/SuchThatClause/FollowsStarClause.h"
#include "Query/Clause/SuchThatClause/ModifiesClause.h"
#include "Query/Clause/SuchThatClause/ParentClause.h"
#include "Query/Clause/SuchThatClause/ParentStarClause.h"
#include "Query/Clause/SuchThatClause/UsesClause.h"
#include "Query/Clause/PatternClause/PatternClause.h"
#include "Query/Clause/PatternClause/AssignmentPattern.h"
#include "../../Utils/ParserUtils.h"
#include "../../simple/Tokenizer/Token.h"
#include "../../simple/Tokenizer/Tokenizer.h"

bool pql::PreprocessorHelper::parse_select_clause(
	std::vector<pql::Token>& token_list,
	pql::SelectClause*& select,
	std::vector<pql::QueryDesignEntity>& design_entities) {

	if (token_list.empty()) {
		return false;
	}

	std::vector<pql::Token>::iterator iter = token_list.begin();
	const std::string select_keyword = "Select";

	if (iter->GetTokenType() != pql::TokenType::kKeyWord || iter->GetToken() != select_keyword) {
		return false;
	}
	++iter;

	if (iter->GetTokenType() != pql::TokenType::kIdentifier) {
		return false;
	}
	std::string identifier = iter->GetToken();
	++iter;

	for (pql::QueryDesignEntity entity: design_entities) {
		if (entity.variableName == identifier) {
			select = new pql::SelectClause(entity);
			token_list = std::vector<pql::Token>(iter, token_list.end());
			return true;
		}
	}

	return false;
}

bool pql::PreprocessorHelper::parse_design_entity(
	std::vector<pql::Token>& token_list,
	std::vector<pql::QueryDesignEntity>& design_entities) {
	if (token_list.empty()) {
		return false;
	}

	std::vector<pql::Token>::iterator iter = token_list.begin();

	pql::DesignEntity entity = get_design_entity(*iter);

	if (entity == pql::DesignEntity::None) {
		return false;
	}
	++iter;

	std::vector<pql::QueryDesignEntity> new_design_entities;

	// Get first synonym
	if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kIdentifier) {
		return false;
	}
	new_design_entities.push_back({ entity, iter->GetToken() });
	++iter;

	// Get the rest
	while (true) {
		if (iter == token_list.end()) {
			return false;
		}

		pql::TokenType type = iter->GetTokenType();
		if (type == pql::TokenType::kStatementEnd) {
			++iter;
			break;
		}
		else if (type == pql::TokenType::kSeparator) {
			++iter;
			if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kIdentifier) {
				return false;
			}
			new_design_entities.push_back({ entity, iter->GetToken() });
			++iter;
		}
		else {
			return false;
		}
	}

	token_list = std::vector<pql::Token>(iter, token_list.end());
	design_entities.insert(design_entities.end(), new_design_entities.begin(), new_design_entities.end());

	return true;
}

pql::DesignEntity pql::PreprocessorHelper::get_design_entity(pql::Token token) {
	// ‘stmt’ | ‘read’ | ‘print’ | ‘while’ | ‘if’ | ‘assign’ | ‘variable’ | ‘constant’ | ‘procedure’
	if (token.GetTokenType() != pql::TokenType::kKeyWord) {
		return pql::DesignEntity::None;
	}

	if (design_entity_map.find(token.GetToken()) == design_entity_map.end()) {
		return pql::DesignEntity::None;
	}

	return design_entity_map.find(token.GetToken())->second;
}

bool pql::PreprocessorHelper::parse_filters(
	std::vector<pql::Token>& token_list, 
	std::vector<pql::FilterClause*>& filters, 
	std::vector<pql::QueryDesignEntity>& design_entities) {
	if (token_list.empty()) {
		return false;
	}

	std::vector<pql::Token>::iterator iter = token_list.begin();
	const std::string such_that_keyword = "such that";
	const std::string pattern_keyword = "pattern";

	if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kKeyWord) {
		return false;
	}

	if (iter->GetToken() == such_that_keyword) {
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kKeyWord) {
			return false;
		}
		ClauseType clause_type = get_clause_type(*iter);
		if (clause_type == ClauseType::None) {
			return false;
		}
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kOpenBracket) {
			return false;
		}
		++iter;

		if (iter == token_list.end()) {
			return false;
		}
		QueryArg first_arg = get_query_arg(*iter, design_entities);
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kSeparator) {
			return false;
		}
		++iter;

		if (iter == token_list.end()) {
			return false;
		}
		QueryArg second_arg = get_query_arg(*iter, design_entities);
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kCloseBracket) {
			return false;
		}
		++iter;

		pql::FilterClause* filter;

		switch (clause_type) {
		case ClauseType::Follows:
			filter = new pql::FollowsClause(first_arg, second_arg);
			break;
		case ClauseType::FollowsStar:
			filter = new pql::FollowsStarClause(first_arg, second_arg);
			break;
		case ClauseType::Modifies:
			filter = new pql::ModifiesClause(first_arg, second_arg);
			break;
		case ClauseType::Parent:
			filter = new pql::ParentClause(first_arg, second_arg);
			break;
		case ClauseType::ParentStar:
			filter = new pql::ParentStarClause(first_arg, second_arg);
			break;
		case ClauseType::Uses:
			filter = new pql::UsesClause(first_arg, second_arg);
			break;
		default:
			return false;
		}

		filters.push_back(filter);
		token_list = std::vector<pql::Token>(iter, token_list.end());
		return true;
	}
	else if (iter->GetToken() == pattern_keyword) {
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != TokenType::kIdentifier) {
			return false;
		}
		QueryArg assignment = get_query_arg(*iter, design_entities);
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kOpenBracket) {
			return false;
		}
		++iter;

		if (iter == token_list.end()) {
			return false;
		}
		QueryArg variable = get_query_arg(*iter, design_entities);
		++iter;

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kSeparator) {
			return false;
		}
		++iter;

		if (iter == token_list.end()) {
			return false;
		}

		std::vector<pql::Token> subtree;
		bool has_underscores = false; /// not for iteration 1
		while (true) {
			subtree.push_back(*iter);
			++iter;
			if (iter == token_list.end()) {
				return false;
			}
			if (iter->GetTokenType() == pql::TokenType::kCloseBracket) {
				break;
			}
		}

		if (iter == token_list.end() || iter->GetTokenType() != pql::TokenType::kCloseBracket) {
			return false;
		}
		++iter;

		std::string postfix = "";

		const std::vector<pql::TokenType> wildcard = { TokenType::kWildCard };
		const std::vector<pql::TokenType> subexpr = { TokenType::kWildCard, TokenType::kConstantString, TokenType::kWildCard };
		const std::vector<pql::TokenType> expr = { TokenType::kConstantString };

		if (match_pattern(subtree, wildcard)) {
			has_underscores = true;
		}
		else if (match_pattern(subtree, subexpr)) {
			has_underscores = true;
			std::string subtree_text = subtree.at(1).GetToken();
			std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
			postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size() - 1);
		}
		else if (match_pattern(subtree, expr)) {
			std::string subtree_text = subtree.at(0).GetToken();
			std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
			postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size() - 1);
		}
		else {
			return false;
		}

		pql::FilterClause* filter = new pql::AssignmentPattern(assignment, variable, postfix);
		filters.push_back(filter);
		token_list = std::vector<pql::Token>(iter, token_list.end());
		return true;
	}
	else {
		return false;
	}
}

bool pql::PreprocessorHelper::match_pattern(std::vector<pql::Token>& tokens, const std::vector<pql::TokenType>& pattern) {
	if (tokens.size() != pattern.size()) {
		return false;
	}
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens.at(i).GetTokenType() != pattern.at(i)) {
			return false;
		}
	}
	return true;
}

pql::ClauseType pql::PreprocessorHelper::get_clause_type(pql::Token token) {
	if (token.GetTokenType() != pql::TokenType::kKeyWord) {
		return pql::ClauseType::None;
	}

	if (clause_type_map.find(token.GetToken()) == clause_type_map.end()) {
		return pql::ClauseType::None;
	}

	return clause_type_map.find(token.GetToken())->second;
}

pql::QueryArg pql::PreprocessorHelper::get_query_arg(
	pql::Token token,
	std::vector<pql::QueryDesignEntity>& design_entities) {
	switch (token.GetTokenType()) {
	case TokenType::kConstantInteger:
		return pql::QueryArg(
			nullptr,
			new pql::QueryArgValue(pql::DesignEntity::Stmt, token.GetToken()), 
			false);
		break;
	case TokenType::kConstantString:
		return pql::QueryArg(
			nullptr,
			new pql::QueryArgValue(pql::DesignEntity::Variable, token.GetToken()),
			false);
		break;
	case TokenType::kWildCard:
		return pql::QueryArg(nullptr, nullptr, true);
		break;
	case TokenType::kIdentifier:
		for (pql::QueryDesignEntity entity : design_entities) {
			if (entity.variableName == token.GetToken()) {
				return pql::QueryArg(
					new pql::QueryDesignEntity(entity.designEntity, entity.variableName),
					nullptr,
					false);
			}
		}
		throw "Variable not declared.";
		break;
	default:
		throw "Cannot parse query argument from token.";
	}
}