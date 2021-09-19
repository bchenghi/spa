#include "Tokenizer.h"
#include "Token.h"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::logic_error;
using std::string;
using std::vector;

vector<pql::Token> pql::Tokenizer::tokenize(string& source)
{
    vector<Token> tokens;
    size_t size = source.size(), pos = 0, lineNumber = 1;

    while (pos < size) next(pos, lineNumber, source, tokens);

    return tokens;
}

void pql::Tokenizer::next(
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

        curr = source[++beginPos];
    }

    bool isConstString = curr == '"', isConstInteger = isdigit(curr), isName = isalpha(curr);

    if (isConstInteger) {
        processConstInteger(beginPos, lineNumber, source, tokens);
        return;
    }
    if (isConstString) {
        processConstString(beginPos, lineNumber, source, tokens);
        return;
    }
    if (isName) {
        processName(beginPos, lineNumber, source, tokens);
        return;
    }

    processSymbol(beginPos, lineNumber, source, tokens);
}

void pql::Tokenizer::processSymbol(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    using std::to_string;

    char curr = source[beginPos];
    size_t endPos = beginPos;
    TokenType type;

    switch (curr) {
        case ',':
        case '_':
        case '(':
        case ')':
        case ';':
            endPos++;
            type = Token::tokenMap.find(curr)->second;
            break;

        default:
            throw logic_error("Invalid " + string(1, curr) + " symbol at line " + to_string(lineNumber));
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));
    beginPos = endPos;
}

void pql::Tokenizer::processConstInteger(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), endPos;

    for (endPos = beginPos + 1; endPos < size; endPos++) {
        char curr = source[endPos];

        if (!isdigit(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (beginPos != endPos)
        tokens.emplace_back(Token(TokenType::CONSTANT_INTEGER, token, lineNumber));
    beginPos = endPos;
}

void pql::Tokenizer::processConstString(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), endPos;
    bool found = false;

    for (endPos = beginPos + 1; endPos < size; endPos++) {
        char curr = source[endPos];

        if (curr == '"') {
            endPos++;
            found = true;
            break;
        }
    }

    if (found) {
        string token = source.substr(beginPos + 1, (endPos - 1) - (beginPos + 1)); // strip the quotes
        tokens.emplace_back(Token(TokenType::CONSTANT_STRING, token, lineNumber));
    }
    beginPos = endPos;
}

void pql::Tokenizer::processName(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), endPos;
    TokenType type = TokenType::IDENTIFIER;
    char curr;

    for (endPos = beginPos; endPos < size; endPos++) {
        curr = source[endPos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (token == "such" && source.substr(beginPos, 9) == "such that") {
        type = TokenType::KEY_WORD;
        token = "such that";
        endPos = beginPos + 9;
    }

    if (Token::keywordSet.find(token) != Token::keywordSet.end()) {
        type = TokenType::KEY_WORD;

        if (curr == '*' && (token == "Follows" || token == "Parent")) {
            token += '*';
            endPos++;
        }
    }

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));
    beginPos = endPos;
}
