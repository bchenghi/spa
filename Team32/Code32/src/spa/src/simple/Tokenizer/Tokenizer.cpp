#include "Tokenizer.h"
#include "Token.h"
#include "Utils/ParserUtils.h"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::isdigit;
using std::isspace;
using std::logic_error;
using std::out_of_range;
using std::string;
using std::vector;

vector<simple::Token> simple::Tokenizer::tokenize(string& source)
{
    trim(source);

    vector<Token> tokens;
    size_t size = source.size(), pos = 0, lineNumber = 1;

    while (pos < size) next(pos, lineNumber, source, tokens);

    return tokens;
}

void simple::Tokenizer::next(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    using std::isalpha;

    char curr = source[beginPos];
    size_t size = source.size();

    while (beginPos < size && isspace(curr)) {
        if (curr == '\n') lineNumber++;
        if (beginPos + 1 >= size) return;

        curr = source.at(++beginPos);
    }

    if (beginPos == size) return;

    bool isConst = isdigit(curr), isName = isalpha(curr);

    if (isConst) {
        processConst(beginPos, lineNumber, source, tokens);
        return;
    }
    if (isName) {
        processName(beginPos, lineNumber, source, tokens);
        return;
    }

    processSymbol(beginPos, lineNumber, source, tokens);
}

void simple::Tokenizer::processSymbol(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    using std::to_string;

    static const std::unordered_map<char, TokenType> tokenMap = {
            { '!', TokenType::NEGATE },
            { '{', TokenType::OPEN_BRACE },
            { '}', TokenType::CLOSE_BRACE },
            { '(', TokenType::OPEN_BRACKET },
            { ')', TokenType::CLOSE_BRACKET },
            { '+', TokenType::OPERATOR },
            { '-', TokenType::OPERATOR },
            { '/', TokenType::OPERATOR },
            { '*', TokenType::OPERATOR },
            { '%', TokenType::OPERATOR },
            { ';', TokenType::STATEMENT_END },
            { '=', TokenType::ASSIGNMENT },
            { '<', TokenType::RELATIONAL_OPERATOR },
            { '>', TokenType::RELATIONAL_OPERATOR }
    };

    char curr = source[beginPos];
    size_t endPos = beginPos, size = source.size();
    TokenType type;

    switch (curr) {
        case ';':
        case '(':
        case ')':
        case '{':
        case '}':
        case '+':
        case '-':
        case '/':
        case '*':
        case '%':
            endPos++;
            type = tokenMap.find(curr)->second;
            break;

        case '<':
        case '>':
            type = tokenMap.find(curr)->second;

            if (endPos + 1 < size && source.at(endPos + 1) == '=') {
                endPos += 2;
                break;
            }

            endPos++;
            break;

        case '!':
            if (endPos + 1 < size && source.at(endPos + 1) == '=') {
                endPos += 2;
                type = TokenType::RELATIONAL_OPERATOR;
                break;
            }

            endPos++;
            type = tokenMap.find(curr)->second;
            break;

        case '&':
            if (endPos + 1 < size && source.at(endPos + 1) == '&') {
                endPos += 2;
                type = TokenType::CONDITION_OPERATOR;
                break;
            }

            throw logic_error("Invalid & symbol at line " + to_string(lineNumber));

        case '|':
            if (endPos + 1 < size && source.at(endPos + 1) == '|') {
                endPos += 2;
                type = TokenType::CONDITION_OPERATOR;
                break;
            }

            throw logic_error("Invalid | symbol at line " + to_string(lineNumber));

        case '=':
            if (endPos + 1 < size && source.at(endPos + 1) == '=') {
                endPos += 2;
                type = TokenType::RELATIONAL_OPERATOR;
                break;
            }

            endPos++;
            type = tokenMap.find(curr)->second;
            break;

        default:
            throw logic_error("Invalid " + string(1, curr) + " symbol at line " + to_string(lineNumber));
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));
    beginPos = endPos;
}

void simple::Tokenizer::processConst(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), endPos;
    char curr = source[beginPos];

    if (beginPos + 1 < size && curr == '0' && isdigit(source[beginPos + 1])) {
        throw logic_error("constant at line " + std::to_string(lineNumber) + " should not begin with 0");
    }

    for (endPos = beginPos + 1; endPos < size; endPos++) {
        curr = source[endPos];

        if (!isdigit(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (beginPos != endPos)
        tokens.emplace_back(Token(TokenType::CONSTANT, token, lineNumber));
    beginPos = endPos;
}

void simple::Tokenizer::processName(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), endPos;
    TokenType type = TokenType::NAME;

    for (endPos = beginPos; endPos < size; endPos++) {
        char curr = source[endPos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));
    beginPos = endPos;
}
