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
        Token currToken = statement.statementTokens.at(curr);

        if (currToken.getTokenType() != expectedTokenType)
            throwWithToken(expectedToken, currToken.getToken(), currToken.getLineNumber());
    } catch (out_of_range& err) {
        throwWithoutToken(
            expectedToken,
            statement.statementTokens.at(curr - 1).getLineNumber()
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

    switch (currToken.getTokenType()) {
        case TokenType::OPEN_BRACKET:
            curr = validateExpressionHelper(curr + 1, expressionTokens);

            try {
                currToken = expressionTokens.at(curr++);

                if (currToken.getTokenType() != TokenType::CLOSE_BRACKET)
                    throw logic_error("Invalid expression");
            } catch (out_of_range& err) {
                throw logic_error("Invalid expression");
            }

            try {
                currToken = expressionTokens.at(curr);

                if (currToken.getTokenType() != TokenType::OPERATOR)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = validateExpressionHelper(curr + 1, expressionTokens);

            break;

        case TokenType::IDENTIFIER:
        case TokenType::CONSTANT:
            try {
                currToken = expressionTokens.at(++curr);

                if (currToken.getTokenType() != TokenType::OPERATOR)
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
    if (statement.statementTokens.size() < 1) {
        throw logic_error("Something went wrong while parsing statement " + to_string(statement.statementNumber));
    }

    const Token& firstToken = statement.statementTokens[0];
    string varName;

    switch (firstToken.getTokenType()) {
        case TokenType::IDENTIFIER:
            varName = firstToken.getToken();

//            cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;

            VarTable::addVar(varName);
            TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, statement.statementNumber);

            this->parseAssignmentStatement(statement);
            break;
        case TokenType::KEY_WORD:
            this->parseKeywordStatement(firstToken, statement);
            break;
        default:
            throw logic_error("Unexpected token '" + firstToken.getToken()
                              + "' at line " + to_string(firstToken.getLineNumber()));
    }
}

void simple::StatementParser::parseAssignmentStatement(const Statement& statement)
{
    size_t curr = 0, expressionEndIndex;
    Token currToken = statement.statementTokens[0];

    if (statement.statementTokens.size() < ASSIGN_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid assignment statement at line " + to_string(currToken.getLineNumber()));

    validateToken(curr, statement, TokenType::IDENTIFIER, "Variable");

    Token identifierToken = statement.statementTokens.at(curr++);
    string varName = identifierToken.getToken();

    /*
    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Modifies(" << statement.statementNumber << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Modifies(\"" << statement.procedureName << "\", \"" << varName << "\")" << endl;
     */

    VarTable::addVar(varName);
    ModifyTable::addStmtModify(statement.statementNumber, varName);
    ModifyTable::addProcModify(statement.procedureName, varName);

    validateToken(curr++, statement, TokenType::ASSIGNMENT, "'='");
    expressionEndIndex = this->parseExpression(curr, statement);
    validateToken(expressionEndIndex, statement, TokenType::STATEMENT_END, "';'");
    vector<string> postfixExpression = tokenToPostfixExpression(
        statement.statementTokens,
        curr,
        expressionEndIndex
    );

    /*
    cout << "[Statement Parser] Adding postfix string for statement " << statement.statementNumber << ": ";
    for (const string& val : postfixExpression) cout << val;
    cout << endl;
     */

    AssignPostFixTable::addPostFix(statement.statementNumber, postfixExpression);
}

void simple::StatementParser::parseKeywordStatement(const Token& firstToken, const Statement& statement)
{
    string keyword = firstToken.getToken();
    size_t lineNumber = firstToken.getLineNumber();

    if (keyword == "read") {
//        cout << "[Statement Parser] Adding type READ for statement " << statement.statementNumber << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::READ, statement.statementNumber);
        this->parseReadStatement(lineNumber, statement);
        return;
    }

    if (keyword == "print") {
//        cout << "[Statement Parser] Adding type PRINT for statement " << statement.statementNumber << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::PRINT, statement.statementNumber);
        this->parsePrintStatement(lineNumber, statement);
        return;
    }

    if (keyword == "call") {
//        cout << "[Statement Parser] Adding type CALL for statement " << statement.statementNumber << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::CALL, statement.statementNumber);
        this->parseCallStatement(lineNumber, statement);
        return;
    }

    if (keyword == "while") {
//        cout << "[Statement Parser] Adding type WHILE for statement " << statement.statementNumber << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, statement.statementNumber);
        this->parseWhileStatement(lineNumber, statement);
        return;
    }

    if (keyword == "if") {
//        cout << "[Statement Parser] Adding type IF for statement " << statement.statementNumber << endl;
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, statement.statementNumber);
        this->parseIfStatement(lineNumber, statement);
        return;
    }

    throw logic_error("Invalid " + keyword + " at line " + to_string(firstToken.getLineNumber()));
}

void simple::StatementParser::parseReadStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statementTokens.size() != READ_STATEMENT_SIZE)
        throw logic_error("Invalid read statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statementTokens[1];
    Token statementEndToken = statement.statementTokens[2];

    if (identifierToken.getTokenType() != TokenType::IDENTIFIER)
        throwWithToken("Identifier", identifierToken.getToken(), identifierToken.getLineNumber());

    if (statementEndToken.getTokenType() != TokenType::STATEMENT_END)
        throwWithToken("';'", statementEndToken.getToken(), statementEndToken.getLineNumber());

    string varName = identifierToken.getToken();

    /*
    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Modifies(" << statement.statementNumber << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Modifies(\"" << statement.procedureName << "\", \"" << varName << "\")" << endl;
     */

    VarTable::addVar(varName);
    ModifyTable::addStmtModify(statement.statementNumber, varName);
    ModifyTable::addProcModify(statement.procedureName, varName);
}

void simple::StatementParser::parsePrintStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statementTokens.size() != PRINT_STATEMENT_SIZE)
        throw logic_error("Invalid print statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statementTokens[1];
    Token statementEndToken = statement.statementTokens[2];

    if (identifierToken.getTokenType() != TokenType::IDENTIFIER)
        throwWithToken("Identifier", identifierToken.getToken(), identifierToken.getLineNumber());

    if (statementEndToken.getTokenType() != TokenType::STATEMENT_END)
        throwWithToken("';'", statementEndToken.getToken(), statementEndToken.getLineNumber());

    string varName = identifierToken.getToken();

    /*
    cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
    cout << "[Statement Parser] Adding Uses(" << statement.statementNumber << ", \"" << varName << "\")" << endl;
    cout << "[Statement Parser] Adding Uses(\"" << statement.procedureName << "\", \"" << varName << "\")" << endl;
     */

    VarTable::addVar(varName);
    UseTable::addStmtUse(statement.statementNumber, varName);
    UseTable::addProcUse(statement.procedureName, varName);
}

void simple::StatementParser::parseCallStatement(size_t lineNumber, const Statement& statement)
{
    using std::unordered_set;

    if (statement.statementTokens.size() != CALL_STATEMENT_SIZE)
        throw logic_error("Invalid call statement at line " + to_string(lineNumber));

    Token identifierToken = statement.statementTokens[1];
    Token statementEndToken = statement.statementTokens[2];

    if (identifierToken.getTokenType() != TokenType::IDENTIFIER)
        throwWithToken("Identifier", identifierToken.getToken(), identifierToken.getLineNumber());

    if (statementEndToken.getTokenType() != TokenType::STATEMENT_END)
        throwWithToken("';'", statementEndToken.getToken(), statementEndToken.getLineNumber());

    string varName = identifierToken.getToken();

    unordered_set<string> usedVars = UseTable::getProcUse(varName);
    unordered_set<string> modifiedVars = ModifyTable::getProcModify(varName);

//    cout << "[Statement Parser] Adding used variables for call stmt " << statement.statementNumber << endl;
    for (const string& usedVar : usedVars) {
        /*
        cout << "[Statement Parser] Adding Uses(" << statement.statementNumber << ", \"" << usedVar << "\")" << endl;
        cout << "[Statement Parser] Adding Uses(\"" << statement.procedureName << "\", \"" << usedVar << "\")" << endl;
         */

        UseTable::addStmtUse(statement.statementNumber, usedVar);
        UseTable::addProcUse(statement.procedureName, usedVar);
    }
//    cout << "[Statement Parser] Finished adding used variables" << endl;

//    cout << "[Statement Parser] Adding modified variables for call stmt " << statement.statementNumber << endl;
    for (const string& modifiedVar : modifiedVars) {
        /*
        cout << "[Statement Parser] Adding Modifies(" << statement.statementNumber
            << ", \"" << modifiedVar << "\")" << endl;
        cout << "[Statement Parser] Adding Modifies(\"" << statement.procedureName
            << "\", \"" << modifiedVar << "\")" << endl;
         */

        ModifyTable::addStmtModify(statement.statementNumber, modifiedVar);
        ModifyTable::addProcModify(statement.procedureName, modifiedVar);
    }
//    cout << "[Statement Parser] Finished adding modified variables" << endl;
}

void simple::StatementParser::parseWhileStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statementTokens.size() < WHILE_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid while statement at line " + to_string(lineNumber));

    size_t curr = 1;

    validateToken(curr++, statement, TokenType::OPEN_BRACKET, "'('");

    curr = this->parseConditionExpression(curr, statement);

    validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");
    validateToken(curr, statement, TokenType::OPEN_BRACE, "'{'");
}

void simple::StatementParser::parseIfStatement(size_t lineNumber, const Statement& statement)
{
    if (statement.statementTokens.size() < IF_STATEMENT_MINIMUM_SIZE)
        throw logic_error("Invalid if statement at line " + to_string(lineNumber));

    size_t curr = 1;
    Token currToken;

    validateToken(curr++, statement, TokenType::OPEN_BRACKET, "'('");

    curr = this->parseConditionExpression(curr, statement);

    validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");
    validateToken(curr, statement, TokenType::KEY_WORD, "'then'");

    currToken = statement.statementTokens[curr++];

    if (currToken.getToken() != "then")
        throwWithToken("'then'", currToken.getToken(), currToken.getLineNumber());

    validateToken(curr, statement, TokenType::OPEN_BRACE, "'{'");
}

size_t simple::StatementParser::parseConditionExpression(size_t curr, const Statement& statement)
{
    Token currToken;

    try {
        currToken = statement.statementTokens.at(curr);

        if (statement.statementTokens.size() - curr < CONDITION_EXPRESSION_MINIMUM_SIZE)
            throw logic_error("Invalid condition expression at line " + to_string(currToken.getLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid condition expression at line "
            + to_string(statement.statementTokens.at(curr - 1).getLineNumber()));
    }

    switch (currToken.getTokenType()) {
        case TokenType::NEGATE:
            validateToken(++curr, statement, TokenType::OPEN_BRACKET, "'('");
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");
            break;

        case TokenType::OPEN_BRACKET:
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");

            try {
                currToken = statement.statementTokens.at(curr);

                if (currToken.getTokenType() != TokenType::CONDITION_OPERATOR)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            validateToken(++curr, statement, TokenType::OPEN_BRACKET, "'('");
            curr = this->parseConditionExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");
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
        currToken = statement.statementTokens.at(curr);

        if (statement.statementTokens.size() - curr < RELATIONAL_EXPRESSION_SIZE)
            throw logic_error("Invalid relational expression at line " + to_string(currToken.getLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid relational expression at line "
            + to_string(statement.statementTokens.at(curr - 1).getLineNumber()));
    }

    curr = this->parseExpression(curr, statement);
    validateToken(
        curr++,
        statement,
        TokenType::RELATIONAL_OPERATOR,
        "Relational operators '>', '>=', '<', '<=', '==', '!='"
    );
    curr = this->parseExpression(curr, statement);

    return curr;
}

size_t simple::StatementParser::parseExpression(size_t curr, const Statement& statement)
{
    Token currToken;

    try {
        currToken = statement.statementTokens.at(curr);

        if (statement.statementTokens.size() - curr < EXPRESSION_SIZE)
            throw logic_error("Invalid expression at line " + to_string(currToken.getLineNumber()));
    } catch (out_of_range& err) {
        throw logic_error("Invalid expression at line "
            + to_string(statement.statementTokens.at(curr - 1).getLineNumber()));
    }

    string varName;

    switch (currToken.getTokenType()) {
        case TokenType::OPEN_BRACKET:
            curr = this->parseExpression(curr + 1, statement);
            validateToken(curr++, statement, TokenType::CLOSE_BRACKET, "')'");

            try {
                currToken = statement.statementTokens.at(curr);

                if (currToken.getTokenType() != TokenType::OPERATOR)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = this->parseExpression(curr + 1, statement);

            break;

        case TokenType::IDENTIFIER:
            varName = currToken.getToken();

            /*
            cout << "[Statement Parser] Adding variable to VarTable: " << varName << endl;
            cout << "[Statement Parser] Adding Uses(" << statement.statementNumber << ", \"" << varName << "\")" << endl;
            cout << "[Statement Parser] Adding Uses(\"" << statement.procedureName << "\", \"" << varName << "\")" << endl;
             */

            VarTable::addVar(varName);
            UseTable::addStmtUse(statement.statementNumber, varName);
            UseTable::addProcUse(statement.procedureName, varName);

        case TokenType::CONSTANT:
            if (currToken.getTokenType() == TokenType::CONSTANT) {
                try {
                    ConstantTable::addConstant(std::stoi(currToken.getToken()));
//                    cout << "[Statement Parser] Adding constant to ConstantTable: " << currToken.getToken() << endl;
                } catch (std::invalid_argument& err) {
                    throwWithToken("Constant", currToken.getToken(), currToken.getLineNumber());
                }
            }

            try {
                currToken = statement.statementTokens.at(++curr);

                if (currToken.getTokenType() != TokenType::OPERATOR)
                    return curr;
            } catch (out_of_range& err) {
                return curr;
            }

            curr = this->parseExpression(curr + 1, statement);
            break;

        default:
            throw logic_error("Invalid expression at line " + to_string(currToken.getLineNumber()));
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
