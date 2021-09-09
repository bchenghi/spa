#include "StatementParser.h"
#include "simple/Tokenizer/Token.h"

#include <string>
#include <stdexcept>

using std::logic_error;
using std::out_of_range;
using std::to_string;
using std::string;

const size_t ASSIGN_STATEMENT_MINIMUM_SIZE = 4;
const size_t READ_STATEMENT_SIZE = 3;
const size_t PRINT_STATEMENT_SIZE = 3;
const size_t CALL_STATEMENT_SIZE = 3;
const size_t WHILE_STATEMENT_MINIMUM_SIZE = 7;
const size_t IF_STATEMENT_MINIMUM_SIZE = 8;

const size_t CONDITION_EXPRESSION_MINIMUM_SIZE = 3;
const size_t RELATIONAL_EXPRESSION_SIZE = 3;
const size_t EXPRESSION_SIZE = 1;

void throwWithoutToken(string expectedToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected at line " + to_string(lineNumber));
}

void throwWithToken(string expectedToken, string actualToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected instead of '"
        + actualToken + "' at line " + to_string(lineNumber));
}

void validateToken(
    size_t curr,
    const simple::Statement& statement,
    simple::TokenType expectedTokenType,
    string expectedToken
) {
    using simple::Statement;
    using simple::Token;

    try {
        Token currToken = statement.statement_tokens.at(curr);

        if (currToken.GetTokenType() != expectedTokenType)
            throwWithToken(expectedToken, currToken.GetToken(), currToken.GetLineNumber());
    } catch (out_of_range& err) {
        throwWithoutToken(
            expectedToken,
            statement.statement_tokens.at(curr - 1).GetLineNumber()
        );
    }
}

simple::StatementParser::StatementParser() {/* insert pkb here */}

void simple::StatementParser::parse(const Statement& statement)
{
    if (statement.statement_tokens.size() < 1) {
        throw logic_error("Something went wrong while parsing statement " + to_string(statement.statement_number));
    }

    const Token& firstToken = statement.statement_tokens[0];

    switch (firstToken.GetTokenType()) {
        case TokenType::kIdentifier:
            // TODO: check if identifier is in variable table, if not exists, add into variable table

            this->parseAssignmentStatement(statement);
            break;
        case TokenType::kKeyWord:
            this->parseKeywordStatement(firstToken, statement);
            break;
        default:
            throw logic_error("Unexpected token '" + firstToken.GetToken()
                              + "' at line " + to_string(firstToken.GetLineNumber()));
    }
}

void simple::StatementParser::parseAssignmentStatement(const Statement& statement)
{
    size_t curr = 0;
    Token currToken = statement.statement_tokens[0];

    if (statement.statement_tokens.size() < ASSIGN_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid assignment statement at line " + to_string(currToken.GetLineNumber()));

    validateToken(curr++, statement, TokenType::kIdentifier, "Variable");

    // TODO: check if identifier is in variable table, if not exists, add into variable table
    // TODO: add to Modifies table => 1. current procedure modifies variable, 2. statement# modifies variable
    // TODO: add to assignment pattern table

    validateToken(curr++, statement, TokenType::kAssignment, "'='");
    curr = this->parseExpression(curr, statement);
    validateToken(curr, statement, TokenType::kStatementEnd, "';'");
}

void simple::StatementParser::parseKeywordStatement(const Token& firstToken, const Statement& statement)
{
    string keyword = firstToken.GetToken();
    size_t lineNumber = firstToken.GetLineNumber();

    if (keyword == "read") {
        this->parseReadStatement(lineNumber, statement);
        return;
    }

    if (keyword == "print") {
        this->parsePrintStatement(lineNumber, statement);
        return;
    }

    if (keyword == "call") {
        this->parseCallStatement(lineNumber, statement);
        return;
    }

    if (keyword == "while") {
        this->parseWhileStatement(lineNumber, statement);
        return;
    }

    if (keyword == "if") {
        this->parseIfStatement(lineNumber, statement);
        return;
    }

    throw logic_error("Invalid " + keyword + " at line " + to_string(firstToken.GetLineNumber()));
}

void simple::StatementParser::parseReadStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statement_tokens.size() != READ_STATEMENT_SIZE)
        throw logic_error("Invalid read statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statement_tokens[1];
    Token statementEndToken = statement.statement_tokens[2];

    if (identifierToken.GetTokenType() != TokenType::kIdentifier)
        throwWithToken("Identifier", identifierToken.GetToken(), identifierToken.GetLineNumber());

    if (statementEndToken.GetTokenType() != TokenType::kStatementEnd)
        throwWithToken("';'", statementEndToken.GetToken(), statementEndToken.GetLineNumber());

    // TODO: check if identifier is in variable table, if not exists, add into variable table
    // TODO: add to Modifies table => 1. current procedure modifies variable, 2. statement# modifies variable
}

void simple::StatementParser::parsePrintStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statement_tokens.size() != PRINT_STATEMENT_SIZE)
        throw logic_error("Invalid print statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statement_tokens[1];
    Token statementEndToken = statement.statement_tokens[2];

    if (identifierToken.GetTokenType() != TokenType::kIdentifier)
        throwWithToken("Identifier", identifierToken.GetToken(), identifierToken.GetLineNumber());

    if (statementEndToken.GetTokenType() != TokenType::kStatementEnd)
        throwWithToken("';'", statementEndToken.GetToken(), statementEndToken.GetLineNumber());

    // TODO: check if identifier is in variable table, if not exists, add into variable table
    // TODO: add to Uses table => 1. current procedure uses variable, 2. statement# uses variable
}

void simple::StatementParser::parseCallStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statement_tokens.size() != CALL_STATEMENT_SIZE)
        throw logic_error("Invalid call statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statement_tokens[1];
    Token statementEndToken = statement.statement_tokens[2];

    if (identifierToken.GetTokenType() != TokenType::kIdentifier)
        throwWithToken("Identifier", identifierToken.GetToken(), identifierToken.GetLineNumber());

    if (statementEndToken.GetTokenType() != TokenType::kStatementEnd)
        throwWithToken("';'", statementEndToken.GetToken(), statementEndToken.GetLineNumber());

    // TODO: check if identifier is in procedure table, if not exists, add into procedure table
    // TODO: add to Uses/Modifies table => based on what the called procedure Uses/Modifies
}

void simple::StatementParser::parseWhileStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statement_tokens.size() < WHILE_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid while statement at line " + to_string(lineNumber));

    size_t curr = 1;

    validateToken(curr++, statement, TokenType::kOpenBracket, "'('");

    curr = this->parseConditionExpression(curr, statement);

    validateToken(curr++, statement, TokenType::kCloseBracket, "')'");
    validateToken(curr, statement, TokenType::kOpenBrace, "'{'");
}

void simple::StatementParser::parseIfStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statement_tokens.size() < IF_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid if statement at line " + to_string(lineNumber));

    size_t curr = 1;
    Token currToken;

    validateToken(curr++, statement, TokenType::kOpenBracket, "'('");

    curr = this->parseConditionExpression(curr, statement);

    validateToken(curr++, statement, TokenType::kCloseBracket, "')'");
    validateToken(curr, statement, TokenType::kKeyWord, "'then'");

    currToken = statement.statement_tokens[curr++];

    if (currToken.GetToken() != "then")
        throwWithToken("'then'", currToken.GetToken(), currToken.GetLineNumber());

    validateToken(curr, statement, TokenType::kOpenBrace, "'{'");
}

size_t simple::StatementParser::parseConditionExpression(size_t curr, const Statement& statement)
{
    Token currToken;

    try {
        currToken = statement.statement_tokens.at(curr);

        if (statement.statement_tokens.size() - curr < CONDITION_EXPRESSION_MINIMUM_SIZE)
            throw logic_error("Invalid condition expression at line " + to_string(currToken.GetLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid condition expression at line "
            + to_string(statement.statement_tokens.at(curr - 1).GetLineNumber()));
    }

    switch (currToken.GetTokenType()) {
        case TokenType::kNegate:
            validateToken(++curr, statement, TokenType::kOpenBracket, "'('");
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::kCloseBracket, "')'");
            break;

        case TokenType::kOpenBracket:
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::kCloseBracket, "')'");

            try {
                currToken = statement.statement_tokens.at(curr);

                if (currToken.GetTokenType() != TokenType::kConditionOperator)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            validateToken(++curr, statement, TokenType::kOpenBracket, "'('");
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::kCloseBracket, "')'");
            break;

        default:
            curr = this->parseRelationalExpression(curr, statement);
            break;
    }

    return curr;
}

size_t simple::StatementParser::parseRelationalExpression(size_t curr, const Statement& statement)
{
    Token currToken;

    try {
        currToken = statement.statement_tokens.at(curr);

        if (statement.statement_tokens.size() - curr < RELATIONAL_EXPRESSION_SIZE)
            throw logic_error("Invalid relational expression at line " + to_string(currToken.GetLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid relational expression at line "
            + to_string(statement.statement_tokens.at(curr - 1).GetLineNumber()));
    }

    curr = this->parseExpression(curr, statement);
    validateToken(
        curr++,
        statement,
        TokenType::kRelationalOperator,
        "Relational operators '>', '>=', '<', '<=', '==', '!='"
    );
    curr = this->parseExpression(curr, statement);

    return curr;
}

size_t simple::StatementParser::parseExpression(size_t curr, const Statement& statement)
{
    Token currToken;

    try {
        currToken = statement.statement_tokens.at(curr);

        if (statement.statement_tokens.size() - curr < EXPRESSION_SIZE)
            throw logic_error("Invalid expression at line " + to_string(currToken.GetLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid expression at line "
            + to_string(statement.statement_tokens.at(curr - 1).GetLineNumber()));
    }

    switch (currToken.GetTokenType()) {
        case TokenType::kOpenBracket:
            curr = this->parseExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::kCloseBracket, "')'");

            try {
                currToken = statement.statement_tokens.at(curr);

                if (currToken.GetTokenType() != TokenType::kOperator)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = this->parseExpression(curr + 1, statement);

            break;

        case TokenType::kIdentifier:
            // TODO: check if identifier is in variable table, if not exists, add into variable table
            // TODO: add to Uses table => 1. current procedure uses variable, 2. statement# uses variable

        case TokenType::kConstant:
            try {
                currToken = statement.statement_tokens.at(++curr);

                if (currToken.GetTokenType() != TokenType::kOperator)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = this->parseExpression(curr + 1, statement);
            break;

        default:
            throw logic_error("Invalid expression at line " + to_string(currToken.GetLineNumber()));
    }

    return curr;
}
