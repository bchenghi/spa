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

using std::cout;
using std::endl;
using std::logic_error;
using std::out_of_range;
using std::string;
using std::unordered_set;
using std::vector;

const size_t SUCH_THAT_SIZE = 9;
const size_t PROG_LINE_SIZE = 9;

vector<pql::Token> pql::Tokenizer::tokenize(string& source)
{
    trim(source);

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

        try {
            curr = source.at(++beginPos);
        } catch (out_of_range& err) {
            return;
        }
    }

    if (beginPos == size) return;

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

    static const std::unordered_map<char, TokenType> tokenMap = {
            { ',', TokenType::SEPARATOR },
            { '_', TokenType::WILD_CARD },
            { '(', TokenType::OPEN_BRACKET },
            { ')', TokenType::CLOSE_BRACKET },
            { ';', TokenType::STATEMENT_END },
            { '<', TokenType::OPEN_TUPLE },
            { '>', TokenType::CLOSE_TUPLE },
            { '=', TokenType::EQUAL_OPERATOR },
            { '.', TokenType::MEMBER_OPERATOR }
    };

    char curr = source[beginPos];
    size_t endPos = beginPos;
    TokenType type;

    switch (curr) {
        case ',':
        case '_':
        case '(':
        case ')':
        case ';':
        case '<':
        case '>':
        case '=':
        case '.':
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

    if (!found) throw logic_error("'\"' expected at line " + std::to_string(lineNumber));

    string token = source.substr(beginPos + 1, (endPos - 1) - (beginPos + 1));  // strip the quotes
    beginPos = endPos;
    tokens.emplace_back(Token(TokenType::CONSTANT_STRING, token, lineNumber));
}

bool canHaveStar(const string& token)
{
    static const unordered_set<string> tokenWithStarMap = {
        "Follows",
        "Parent",
        "Calls",
        "Next",
        "Affects"
    };

    return tokenWithStarMap.find(token) != tokenWithStarMap.end();
}

void pql::Tokenizer::processName(
    size_t& beginPos,
    size_t& lineNumber,
    string& source,
    vector<Token>& tokens
) {
    static const unordered_set<string> keywordSet = {
        "Select",
        "Follows",
        "Parent",
        "Uses",
        "Modifies",
        "Calls",
        "Next",
        "Affects",
        "pattern",
        "stmt",
        "read",
        "print",
        "call",
        "while",
        "if",
        "assign",
        "variable",
        "constant",
        "procedure",
        "and",
        "with"
    };
    static const unordered_set<string> attrNameSet = {
        "procName",
        "varName",
        "value"
    };

    size_t size = source.size(), endPos;
    TokenType type = TokenType::IDENTIFIER;
    char curr;

    for (endPos = beginPos; endPos < size; endPos++) {
        curr = source[endPos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(beginPos, endPos - beginPos);

    if (token == "such" && source.substr(beginPos, SUCH_THAT_SIZE) == "such that") {
        type = TokenType::KEY_WORD;
        token = "such that";
        endPos = beginPos + 9;
    }

    if (token == "prog" && source.substr(beginPos, PROG_LINE_SIZE) == "prog_line") {
        type = TokenType::KEY_WORD;
        token = "prog_line";
        endPos = beginPos + 9;
    }

    if (keywordSet.find(token) != keywordSet.end()) {
        type = TokenType::KEY_WORD;

        if (curr == '*' && canHaveStar(token)) {
            token += '*';
            endPos++;
        }

        if (curr == '#' && token == "stmt") {
            type = TokenType::ATTRIBUTE_NAME;
            token += '#';
            endPos++;
        }
    }

    if (attrNameSet.find(token) != attrNameSet.end())
        type = TokenType::ATTRIBUTE_NAME;

    if (beginPos != endPos)
        tokens.emplace_back(Token(type, token, lineNumber));

    beginPos = endPos;
}
