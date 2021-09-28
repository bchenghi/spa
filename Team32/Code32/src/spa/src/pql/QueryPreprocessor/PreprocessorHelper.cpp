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
#include "../../simple/SourceProcessor/StatementParser.h"

bool pql::PreprocessorHelper::parse_select_clause(
    std::vector<pql::Token>& tokenList,
    pql::SelectClause*& select,
    std::vector<pql::QueryDesignEntity>& designEntities
) {
    if (tokenList.empty()) {
        return false;
    }

    std::vector<pql::Token>::iterator iter = tokenList.begin();
    const std::string select_keyword = "Select";

    if (iter->getTokenType() != pql::TokenType::KEY_WORD || iter->getToken() != select_keyword) {
        return false;
    }
    ++iter;

    if (iter->getTokenType() != pql::TokenType::IDENTIFIER) {
        return false;
    }
    std::string identifier = iter->getToken();
    ++iter;

    for (const pql::QueryDesignEntity& entity: designEntities) {
        if (entity.variableName == identifier) {
            select = new pql::SelectClause({entity});
            tokenList = std::vector<pql::Token>(iter, tokenList.end());
            return true;
        }
    }

    return false;
}

bool pql::PreprocessorHelper::parse_design_entity(
    std::vector<pql::Token>& tokenList,
    std::vector<pql::QueryDesignEntity>& designEntities) {
    if (tokenList.empty()) {
        return false;
    }

    std::vector<pql::Token>::iterator iter = tokenList.begin();

    pql::DesignEntity entity = get_design_entity(*iter);

    if (entity == pql::DesignEntity::NONE) {
        return false;
    }
    ++iter;

    std::vector<pql::QueryDesignEntity> new_design_entities;

    // Get first synonym
    if (iter == tokenList.end() || iter->getTokenType() != pql::TokenType::IDENTIFIER) {
        return false;
    }
    new_design_entities.push_back({ entity, iter->getToken() });
    ++iter;

    // Get the rest
    while (true) {
        if (iter == tokenList.end()) {
            return false;
        }

        pql::TokenType type = iter->getTokenType();
        if (type == pql::TokenType::STATEMENT_END) {
            ++iter;
            break;
        }
        else if (type == pql::TokenType::SEPARATOR) {
            ++iter;
            if (iter == tokenList.end() || iter->getTokenType() != pql::TokenType::IDENTIFIER) {
                return false;
            }
            new_design_entities.push_back({ entity, iter->getToken() });
            ++iter;
        }
        else {
            return false;
        }
    }

    tokenList = std::vector<pql::Token>(iter, tokenList.end());
    designEntities.insert(designEntities.end(), new_design_entities.begin(), new_design_entities.end());

    return true;
}

pql::DesignEntity pql::PreprocessorHelper::get_design_entity(const pql::Token& token) {
    // �stmt� | �read� | �print� | �while� | �if� | �assign� | �variable� | �constant� | �procedure�
    if (token.getTokenType() != pql::TokenType::KEY_WORD) {
        return pql::DesignEntity::NONE;
    }

    if (designEntityMap.find(token.getToken()) == designEntityMap.end()) {
        return pql::DesignEntity::NONE;
    }

    return designEntityMap.find(token.getToken())->second;
}

bool pql::PreprocessorHelper::parse_filters(
    std::vector<pql::Token>& token_list, 
    std::vector<pql::FilterClause*>& filters, 
    std::vector<pql::QueryDesignEntity>& designEntities) {
    if (token_list.empty()) {
        return false;
    }

    std::vector<pql::Token>::iterator iter = token_list.begin();
    const std::string such_that_keyword = "such that";
    const std::string pattern_keyword = "pattern";

    if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::KEY_WORD) {
        return false;
    }

    if (iter->getToken() == such_that_keyword) {
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::KEY_WORD) {
            return false;
        }
        ClauseType clause_type = get_clause_type(*iter);
        if (clause_type == ClauseType::None) {
            return false;
        }
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::OPEN_BRACKET) {
            return false;
        }
        ++iter;

        if (iter == token_list.end()) {
            return false;
        }
        QueryArg first_arg = get_query_arg(*iter, designEntities);
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::SEPARATOR) {
            return false;
        }
        ++iter;

        if (iter == token_list.end()) {
            return false;
        }
        QueryArg second_arg = get_query_arg(*iter, designEntities);
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::CLOSE_BRACKET) {
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
    else if (iter->getToken() == pattern_keyword) {
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != TokenType::IDENTIFIER) {
            return false;
        }
        QueryArg assignment = get_query_arg(*iter, designEntities);
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::OPEN_BRACKET) {
            return false;
        }
        ++iter;

        if (iter == token_list.end()) {
            return false;
        }
        QueryArg variable = get_query_arg(*iter, designEntities);
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::SEPARATOR) {
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
            if (iter->getTokenType() == pql::TokenType::CLOSE_BRACKET) {
                break;
            }
        }

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::CLOSE_BRACKET) {
            return false;
        }
        ++iter;

        std::vector<std::string> postfix;

        const std::vector<pql::TokenType> wildcard = { TokenType::WILD_CARD };
        const std::vector<pql::TokenType> subexpr = {TokenType::WILD_CARD, TokenType::CONSTANT_STRING, TokenType::WILD_CARD };
        const std::vector<pql::TokenType> expr = { TokenType::CONSTANT_STRING };

        if (match_pattern(subtree, wildcard)) {
            has_underscores = true;
        }
        else if (match_pattern(subtree, subexpr)) {
            has_underscores = true;
            std::string subtree_text = subtree.at(1).getToken();
            std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
            if (!simple::validateExpression(tokenized_subtree)) {
                return false;
            }
            postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size());
        }
        else if (match_pattern(subtree, expr)) {
            std::string subtree_text = subtree.at(0).getToken();
            std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
            if (!simple::validateExpression(tokenized_subtree)) {
                return false;
            }
            postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size());
        }
        else {
            return false;
        }

        pql::FilterClause* filter = new pql::AssignmentPattern(assignment, variable, postfix, has_underscores);
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
        if (tokens.at(i).getTokenType() != pattern.at(i)) {
            return false;
        }
    }
    return true;
}

pql::ClauseType pql::PreprocessorHelper::get_clause_type(const pql::Token& token) {
    if (token.getTokenType() != pql::TokenType::KEY_WORD) {
        return pql::ClauseType::None;
    }

    if (clauseTypeMap.find(token.getToken()) == clauseTypeMap.end()) {
        return pql::ClauseType::None;
    }

    return clauseTypeMap.find(token.getToken())->second;
}

pql::QueryArg pql::PreprocessorHelper::get_query_arg(
    const pql::Token& token,
    std::vector<pql::QueryDesignEntity>& designEntities
) {
    switch (token.getTokenType()) {
    case TokenType::CONSTANT_INTEGER:
        return pql::QueryArg(
            nullptr,
            new pql::QueryArgValue(pql::DesignEntity::STMT, token.getToken()),
            false);
        break;
    case TokenType::CONSTANT_STRING:
        return pql::QueryArg(
            nullptr,
            new pql::QueryArgValue(pql::DesignEntity::VARIABLE, token.getToken()),
            false);
        break;
    case TokenType::WILD_CARD:
        return pql::QueryArg(nullptr, nullptr, true);
        break;
    case TokenType::IDENTIFIER:
        for (const pql::QueryDesignEntity& entity : designEntities) {
            if (entity.variableName == token.getToken()) {
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
