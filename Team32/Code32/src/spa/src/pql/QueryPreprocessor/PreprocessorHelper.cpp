#include "PreprocessorHelper.h"
#include "Query/Clause/SuchThatClause/SuchThatClause.h"
#include "Query/Clause/SuchThatClause/FollowsClause.h"
#include "Query/Clause/SuchThatClause/FollowsStarClause.h"
#include "Query/Clause/SuchThatClause/ModifiesClause.h"
#include "Query/Clause/SuchThatClause/ParentClause.h"
#include "Query/Clause/SuchThatClause/ParentStarClause.h"
#include "Query/Clause/SuchThatClause/UsesClause.h"
#include "Query/Clause/SuchThatClause/CallsClause.h"
#include "Query/Clause/SuchThatClause/CallsStarClause.h"
#include "Query/Clause/SuchThatClause/NextClause.h"
#include "Query/Clause/SuchThatClause/NextStarClause.h"
#include "Query/Clause/SuchThatClause/AffectsClause.h"
#include "Query/Clause/SuchThatClause/AffectsStarClause.h"
#include "Query/Clause/PatternClause/PatternClause.h"
#include "Query/Clause/PatternClause/AssignmentPattern.h"
#include "Query/Clause/PatternClause/IfPattern.h"
#include "Query/Clause/PatternClause/WhilePattern.h"
#include "../../Utils/ParserUtils.h"
#include "../../simple/Tokenizer/Token.h"
#include "../../simple/Tokenizer/Tokenizer.h"
#include "../../simple/SourceProcessor/StatementParser.h"

bool find_entity(string identifier, std::vector<pql::QueryDesignEntity> entities, pql::QueryDesignEntity &result) {
    for (pql::QueryDesignEntity entity: entities) {
        if (entity.variableName == identifier) {
            result = entity;
            return true;
        }
    }
    return false;
}

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

    if (iter->getTokenType() == pql::TokenType::IDENTIFIER) {
        std::string identifier = iter->getToken();
        ++iter;

        pql::QueryDesignEntity entity;

        if (find_entity(identifier, designEntities, entity)) {
            select = new pql::SelectClause({entity});
            tokenList = std::vector<pql::Token>(iter, tokenList.end());
            return true;
        }
        else {
            return false;
        }
    }
    else if (iter->getTokenType() == pql::TokenType::BOOLEAN) {
        ++iter;
        select = new pql::SelectClause({});
        tokenList = std::vector<pql::Token>(iter, tokenList.end());
        return true;
    }
    else if (iter->getTokenType() == pql::TokenType::OPEN_TUPLE) {
        ++iter;
        std::vector<pql::QueryDesignEntity> select_entities;
        // Get first entity
        if (iter == tokenList.end() || iter->getTokenType() != pql::TokenType::IDENTIFIER) {
            return false;
        }
        std::string identifier = iter->getToken();
        ++iter;

        pql::QueryDesignEntity entity;

        if (find_entity(identifier, designEntities, entity)) {
            select_entities.push_back(entity);
        }
        else {
            return false;
        }

        // Get the rest
        while (true) {
            if (iter == tokenList.end()) {
                return false;
            }

            pql::TokenType type = iter->getTokenType();
            if (type == pql::TokenType::CLOSE_TUPLE) {
                ++iter;
                break;
            }
            else if (type == pql::TokenType::SEPARATOR) {
                ++iter;
                if (iter == tokenList.end() || iter->getTokenType() != pql::TokenType::IDENTIFIER) {
                    return false;
                }
                identifier = iter->getToken();
                if (find_entity(identifier, designEntities, entity)) {
                    select_entities.push_back(entity);
                }
                else {
                    return false;
                }
                ++iter;
            }
            else {
                return false;
            }
        }

        select = new pql::SelectClause(select_entities);
        tokenList = std::vector<pql::Token>(iter, tokenList.end());
        return true;
    }
    else {
        return false;
    }
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
    // "stmt" | "read" | "print" | "while" | "if" | "assign" | "variable" | "constant" | "procedure"
    if (token.getTokenType() != pql::TokenType::KEY_WORD) {
        return pql::DesignEntity::NONE;
    }

    if (designEntityMap.find(token.getToken()) == designEntityMap.end()) {
        return pql::DesignEntity::NONE;
    }

    return designEntityMap.find(token.getToken())->second;
}

std::string get_clause(std::string current_clause, std::string &last_clause) {
    if (current_clause == "and") {
        current_clause = last_clause;
    }
    else {
        last_clause = current_clause;
    }
    return current_clause;
}

std::vector<pql::TokenType> get_token_types(std::vector<pql::Token>& tokens) {
    std::vector<pql::TokenType> subtree_types;
    for (int i = 0; i < tokens.size(); ++i) {
        subtree_types.push_back(tokens.at(i).getTokenType());
    }
    return subtree_types;
}

bool pql::PreprocessorHelper::parse_filters(
    std::vector<pql::Token>& token_list, 
    std::vector<pql::FilterClause*>& filters, 
    std::vector<pql::QueryDesignEntity>& designEntities,
    std::string &last_clause) {
    if (token_list.empty()) {
        return false;
    }

    std::vector<pql::Token>::iterator iter = token_list.begin();
    const std::string such_that_keyword = "such that";
    const std::string pattern_keyword = "pattern";
    const std::string with_keyword = "with";

    if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::KEY_WORD) {
        return false;
    }

    std::string clause = get_clause(iter->getToken(), last_clause);

    if (clause == such_that_keyword) {
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != pql::TokenType::KEY_WORD) {
            return false;
        }
        ClauseType clause_type = get_clause_type(*iter);
        if (clause_type == ClauseType::NONE) {
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
        case ClauseType::FOLLOWS:
            filter = new pql::FollowsClause(first_arg, second_arg);
            break;
        case ClauseType::FOLLOWSSTAR:
            filter = new pql::FollowsStarClause(first_arg, second_arg);
            break;
        case ClauseType::MODIFIES:
            filter = new pql::ModifiesClause(first_arg, second_arg);
            break;
        case ClauseType::PARENT:
            filter = new pql::ParentClause(first_arg, second_arg);
            break;
        case ClauseType::PARENTSTAR:
            filter = new pql::ParentStarClause(first_arg, second_arg);
            break;
        case ClauseType::USES:
            filter = new pql::UsesClause(first_arg, second_arg);
            break;
        case ClauseType::CALLS:
            filter = new pql::CallsClause(first_arg, second_arg);
            break;
        case ClauseType::CALLSSTAR:
            filter = new pql::CallsStarClause(first_arg, second_arg);
            break;

        case ClauseType::NEXT:
            filter = new pql::NextClause(first_arg, second_arg);
            break;
        case ClauseType::NEXTSTAR:
            filter = new pql::NextStarClause(first_arg, second_arg);
            break;
        /*
        case ClauseType::AFFECTS:
            filter = new pql::AffectsClause(first_arg, second_arg);
            break;
        case ClauseType::AFFECTSSTAR:
            filter = new pql::AffectsStarClause(first_arg, second_arg);
            break;
         */
        default:
            return false;
        }

        filters.push_back(filter);
        token_list = std::vector<pql::Token>(iter, token_list.end());
        return true;
    }
    else if (clause == pattern_keyword) {
        // common prefix between if, while, and assignment patterns: "design_ent(var,"
        ++iter;

        if (iter == token_list.end() || iter->getTokenType() != TokenType::IDENTIFIER) {
            return false;
        }
        QueryArg design_entity = get_query_arg(*iter, designEntities);
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
        // end of common prefix

        std::vector<pql::Token> subtree;
        bool has_underscores = false;
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
        const std::vector<pql::TokenType> subexpr = { TokenType::WILD_CARD, TokenType::CONSTANT_STRING, TokenType::WILD_CARD };
        const std::vector<pql::TokenType> expr = { TokenType::CONSTANT_STRING };
        const std::vector<pql::TokenType> if_pattern = { TokenType::WILD_CARD, TokenType::SEPARATOR, TokenType::WILD_CARD };
        const std::vector<pql::TokenType> while_pattern = { TokenType::WILD_CARD };

        std::vector<pql::TokenType> subtree_types = get_token_types(subtree);

        if (design_entity.queryDesignEntity == nullptr) {
            return false;
        }
        pql::DesignEntity design_entity_type = design_entity.queryDesignEntity->designEntity;

        if (design_entity_type == DesignEntity::ASSIGN) {
            if (subtree_types == wildcard) {
                has_underscores = true;
            } else if (subtree_types == subexpr) {
                has_underscores = true;
                std::string subtree_text = subtree.at(1).getToken();
                std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
                if (!simple::validateExpression(tokenized_subtree)) {
                    return false;
                }
                postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size());
            } else if (subtree_types == expr) {
                std::string subtree_text = subtree.at(0).getToken();
                std::vector<simple::Token> tokenized_subtree = simple::Tokenizer::tokenize(subtree_text);
                if (!simple::validateExpression(tokenized_subtree)) {
                    return false;
                }
                postfix = tokenToPostfixExpression(tokenized_subtree, 0, tokenized_subtree.size());
            } else {
                return false;
            }

            pql::FilterClause *filter = new pql::AssignmentPattern(design_entity, variable, postfix, has_underscores);
            filters.push_back(filter);
            token_list = std::vector<pql::Token>(iter, token_list.end());
            return true;
        }
        else if (design_entity_type == DesignEntity::WHILE) {
            if (subtree_types != while_pattern) {
                return false;
            }
            pql::FilterClause *filter = new pql::WhilePattern(design_entity, variable);
            filters.push_back(filter);
            token_list = std::vector<pql::Token>(iter, token_list.end());
            return true;
        }
        else if (design_entity_type == DesignEntity::IF) {
            if (subtree_types != if_pattern) {
                return false;
            }
            pql::FilterClause *filter = new pql::IfPattern(design_entity, variable);
            filters.push_back(filter);
            token_list = std::vector<pql::Token>(iter, token_list.end());
            return true;
        }
        else {
            return false;
        }
    }
    else if (clause == with_keyword) {
        // TODO
    }
    else {
        return false;
    }
}

pql::ClauseType pql::PreprocessorHelper::get_clause_type(const pql::Token& token) {
    if (token.getTokenType() != pql::TokenType::KEY_WORD) {
        return pql::ClauseType::NONE;
    }

    if (clauseTypeMap.find(token.getToken()) == clauseTypeMap.end()) {
        return pql::ClauseType::NONE;
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
