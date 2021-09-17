#include "StatementParser.h"
#include "PKB/AssignPostFixTable.h"
#include "PKB/ConstantTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "PKB/UseTable.h"
#include "PKB/VarTable.h"
#include "pql/DesignEntity.h"
#include "simple/Tokenizer/Token.h"
#include "Utils/ParserUtils.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_set>

using std::cout;
using std::endl;
using std::logic_error;
using std::out_of_range;
using std::to_string;
using std::string;
using std::vector;

const size_t ASSIGN_STATEMENT_MINIMUM_SIZE = 4;
const size_t READ_STATEMENT_SIZE = 3;
const size_t PRINT_STATEMENT_SIZE = 3;
const size_t CALL_STATEMENT_SIZE = 3;
const size_t WHILE_STATEMENT_MINIMUM_SIZE = 7;
const size_t IF_STATEMENT_MINIMUM_SIZE = 8;

const size_t CONDITION_EXPRESSION_MINIMUM_SIZE = 3;
const size_t RELATIONAL_EXPRESSION_SIZE = 3;
const size_t EXPRESSION_SIZE = 1;

void validateToken(
    size_t curr,
    const simple::Statement& statement,
    simple::TokenType expectedTokenType,
    const string& expectedToken
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

size_t validateExpressionHelper(size_t curr, vector<simple::Token>& expressionTokens)
{
    using simple::Token;
    using simple::TokenType;

    Token currToken;

    try {
        currToken = expressionTokens.at(curr);

        if (expressionTokens.size() - curr < EXPRESSION_SIZE)
            throw logic_error("Invalid expression");
    } catch (out_of_range& err) {
        throw logic_error("Invalid expression");
    }

    switch (currToken.GetTokenType()) {
        case TokenType::kOpenBracket:
            curr = validateExpressionHelper(curr + 1, expressionTokens);

            try {
                currToken = expressionTokens.at(curr++);

                if (currToken.GetTokenType() != TokenType::kCloseBracket)
                    throw logic_error("Invalid expression");
            } catch (out_of_range& err) {
                throw logic_error("Invalid expression");
            }

            try {
                currToken = expressionTokens.at(curr);

                if (currToken.GetTokenType() != TokenType::kOperator)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = validateExpressionHelper(curr + 1, expressionTokens);

            break;

        case TokenType::kIdentifier:
        case TokenType::kConstant:
            try {
                currToken = expressionTokens.at(++curr);

                if (currToken.GetTokenType() != TokenType::kOperator)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = validateExpressionHelper(curr + 1, expressionTokens);
            break;

        default:
            throw logic_error("Invalid expression");
    }

    return curr;
}

simple::StatementParser::StatementParser() {/* insert pkb here */}

void simple::StatementParser::parse(const Statement& statement)
{
    if (statement.statement_tokens.size() < 1) {
        throw logic_error("Something went wrong while parsing statement " + to_string(statement.statement_number));
    }

    const Token& firstToken = statement.statement_tokens[0];
    string varName;

    switch (firstToken.GetTokenType()) {
        case TokenType::kIdentifier:
            varName = firstToken.GetToken();

            cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;

            VarTable::addVar(varName);
            TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, statement.statement_number);

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
    size_t curr = 0, expressionEndIndex;
    Token currToken = statement.statement_tokens[0];

    if (statement.statement_tokens.size() < ASSIGN_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid assignment statement at line " + to_string(currToken.GetLineNumber()));

    validateToken(curr, statement, TokenType::kIdentifier, "Variable");

    Token identifierToken = statement.statement_tokens.at(curr++);
    string varName = identifierToken.GetToken();

    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Modifies(" << statement.statement_number << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Modifies(\"" << statement.procedure_name << "\", \"" << varName << "\")" << endl;

    VarTable::addVar(varName);
    ModifyTable::addStmtModify(statement.statement_number, varName);
    ModifyTable::addProcModify(statement.procedure_name, varName);

    validateToken(curr++, statement, TokenType::kAssignment, "'='");
    expressionEndIndex = this->parseExpression(curr, statement);
    validateToken(expressionEndIndex, statement, TokenType::kStatementEnd, "';'");
    vector<string> postfixExpression = tokenToPostfixExpression(
        statement.statement_tokens,
        curr,
        expressionEndIndex
    );

    cout << "[Statement Parser] Adding postfix string for statement " << statement.statement_number << ": ";
    for (const string& val : postfixExpression) cout << val;
    cout << endl;

    AssignPostFixTable::addPostFix(statement.statement_number, postfixExpression);
}

void simple::StatementParser::parseKeywordStatement(const Token& firstToken, const Statement& statement)
{
    string keyword = firstToken.GetToken();
    size_t lineNumber = firstToken.GetLineNumber();

    if (keyword == "read") {
        cout << "[Statement Parser] Adding type READ for statement " << statement.statement_number << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Read, statement.statement_number);
        this->parseReadStatement(lineNumber, statement);
        return;
    }

    if (keyword == "print") {
        cout << "[Statement Parser] Adding type PRINT for statement " << statement.statement_number << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Print, statement.statement_number);
        this->parsePrintStatement(lineNumber, statement);
        return;
    }

    if (keyword == "call") {
        cout << "[Statement Parser] Adding type CALL for statement " << statement.statement_number << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Call, statement.statement_number);
        this->parseCallStatement(lineNumber, statement);
        return;
    }

    if (keyword == "while") {
        cout << "[Statement Parser] Adding type WHILE for statement " << statement.statement_number << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, statement.statement_number);
        this->parseWhileStatement(lineNumber, statement);
        return;
    }

    if (keyword == "if") {
        cout << "[Statement Parser] Adding type IF for statement " << statement.statement_number << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, statement.statement_number);
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

    string varName = identifierToken.GetToken();

    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Modifies(" << statement.statement_number << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Modifies(\"" << statement.procedure_name << "\", \"" << varName << "\")" << endl;

    VarTable::addVar(varName);
    ModifyTable::addStmtModify(statement.statement_number, varName);
    ModifyTable::addProcModify(statement.procedure_name, varName);
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

    string varName = identifierToken.GetToken();

    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Uses(" << statement.statement_number << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Uses(\"" << statement.procedure_name << "\", \"" << varName << "\")" << endl;

    VarTable::addVar(varName);
    UseTable::addStmtUse(statement.statement_number, varName);
    UseTable::addProcUse(statement.procedure_name, varName);
}

void simple::StatementParser::parseCallStatement(size_t lineNumber, const Statement& statement)
{
    using std::unordered_set;

    if (statement.statement_tokens.size() != CALL_STATEMENT_SIZE)
        throw logic_error("Invalid call statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statement_tokens[1];
    Token statementEndToken = statement.statement_tokens[2];

    if (identifierToken.GetTokenType() != TokenType::kIdentifier)
        throwWithToken("Identifier", identifierToken.GetToken(), identifierToken.GetLineNumber());

    if (statementEndToken.GetTokenType() != TokenType::kStatementEnd)
        throwWithToken("';'", statementEndToken.GetToken(), statementEndToken.GetLineNumber());

    string varName = identifierToken.GetToken();

    unordered_set<string> usedVars = UseTable::getProcUse(varName);
    unordered_set<string> modifiedVars = ModifyTable::getProcModify(varName);

    cout << "[Statement Parser] Adding used variables for call stmt " << statement.statement_number << endl;
    for (const string& usedVar : usedVars) {
        cout << "[Statement Parser] Adding Uses(" << statement.statement_number << ", \"" << usedVar << "\")" << endl;
        cout << "[Statement Parser] Adding Uses(\"" << statement.procedure_name << "\", \"" << usedVar << "\")" << endl;
        UseTable::addStmtUse(statement.statement_number, usedVar);
        UseTable::addProcUse(statement.procedure_name, usedVar);
    }
    cout << "[Statement Parser] Finished adding used variables" << endl;
    for (const string& modifiedVar : modifiedVars) {
        cout << "[Statement Parser] Adding Modifies(" << statement.statement_number
            << ", \"" << modifiedVar << "\")" << endl;
        cout << "[Statement Parser] Adding Modifies(\"" << statement.procedure_name
            << "\", \"" << modifiedVar << "\")" << endl;
        ModifyTable::addStmtModify(statement.statement_number, modifiedVar);
        ModifyTable::addProcModify(statement.procedure_name, modifiedVar);
    }
    cout << "[Statement Parser] Finished adding modified variables" << endl;
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

    string varName;

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
            varName = currToken.GetToken();

            cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
            cout << "[Statement Parser] Adding Uses(" << statement.statement_number << ", \"" << varName << "\")" << endl;
            cout << "[Statement Parser] Adding Uses(\"" << statement.procedure_name << "\", \"" << varName << "\")" << endl;

            VarTable::addVar(varName);
            UseTable::addStmtUse(statement.statement_number, varName);
            UseTable::addProcUse(statement.procedure_name, varName);

        case TokenType::kConstant:
            if (currToken.GetTokenType() == TokenType::kConstant) {
                try {
                    ConstantTable::addConstant(std::stoi(currToken.GetToken()));
                    cout << "[Statement Parser] Adding constant to ConstantTable: " << currToken.GetToken() << endl;
                } catch (std::invalid_argument& err) {
                    throwWithToken("Constant", currToken.GetToken(), currToken.GetLineNumber());
                }
            }

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

bool simple::validateExpression(vector<Token>& expressionTokens)
{
    try {
        size_t end = validateExpressionHelper(0, expressionTokens);

        if (expressionTokens.size() != end)
            return false;

        return true;
    } catch (logic_error& err) {
        return false;
    }
}
