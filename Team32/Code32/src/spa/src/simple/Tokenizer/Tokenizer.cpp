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

        try {
            curr = source.at(++beginPos);
        } catch (out_of_range& err) {
            return;
        }
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
    size_t endPos = beginPos;
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

            try {
                if (source.at(endPos + 1) == '=') {
                    endPos += 2;
                    break;
                }
            } catch (out_of_range& err) { }

            endPos++;
            break;

        case '!':
            try {
                if (source.at(endPos + 1) == '=') {
                    endPos += 2;
                    type = TokenType::RELATIONAL_OPERATOR;
                    break;
                }
            } catch (out_of_range& err) { }

            endPos++;
            type = tokenMap.find(curr)->second;
            break;

        case '&':
            try {
                if (source.at(endPos + 1) == '&') {
                    endPos += 2;
                    type = TokenType::CONDITION_OPERATOR;
                    break;
                }
            } catch (out_of_range& err) { }

            throw logic_error("Invalid & symbol at line " + to_string(lineNumber));

        case '|':
            try {
                if (source.at(endPos + 1) == '|') {
                    endPos += 2;
                    type = TokenType::CONDITION_OPERATOR;
                    break;
                }
            } catch (out_of_range& err) { }

            throw logic_error("Invalid | symbol at line " + to_string(lineNumber));

        case '=':
            try {
                if (source.at(endPos + 1) == '=') {
                    endPos += 2;
                    type = TokenType::RELATIONAL_OPERATOR;
                    break;
                }
            } catch (out_of_range& err) { }

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

    for (endPos = beginPos; endPos < size; endPos++) {
        char curr = source[endPos];

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
    static const std::unordered_set<string> keywordSet = {
            "procedure",
            "read",
            "print",
            "call",
            "while",
            "if",
            "then",
            "else"
    };

    size_t size = source.size(), endPos;
    TokenType type = TokenType::IDENTIFIER;

    for (endPos = beginPos; endPos < size; endPos++) {
        char curr = source[endPos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (keywordSet.find(token) != keywordSet.end())
        type = TokenType::KEY_WORD;

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));
    beginPos = endPos;
}
