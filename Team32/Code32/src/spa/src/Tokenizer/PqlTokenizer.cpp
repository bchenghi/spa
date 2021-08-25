#include "PqlTokenizer.h"
#include "Token/PqlToken.h"

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

vector<pql::PqlToken> pql::PqlTokenizer::tokenize(string& source)
{
    vector<PqlToken> tokens;
    size_t size = source.size(), pos = 0, line_number = 1;

    while (pos < size) {
        try {
            next(pos, line_number, source, tokens);
        } catch (logic_error& err) {
            // TODO: Handle error
            cout << err.what() << endl;
            throw err;
        }
    }

    return tokens;
}

void pql::PqlTokenizer::next(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& tokens
) {
    using std::isalpha;

    char curr = source[begin_pos];
    size_t size = source.size();

    while (begin_pos < size && isspace(curr)) {
        if (curr == '\n') line_number++;

        curr = source[++begin_pos];
    }

    bool is_const_string = curr == '"', is_const_integer = isdigit(curr), is_name = isalpha(curr);

    if (is_const_integer) {
        processConstInteger(begin_pos, line_number, source, tokens);
        return;
    }
    if (is_const_string) {
        processConstString(begin_pos, line_number, source, tokens);
        return;
    }
    if (is_name) {
        processName(begin_pos, line_number, source, tokens);
        return;
    }

    processSymbol(begin_pos, line_number, source, tokens);
}

void pql::PqlTokenizer::processSymbol(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& tokens
) {
    using std::to_string;

    char curr = source[begin_pos];
    size_t end_pos = begin_pos;
    TokenType type;

    switch (curr) {
        case ',':
        case '_':
        case '(':
        case ')':
        case ';':
            end_pos++;
            type = PqlToken::token_map.find(curr)->second;
            break;

        default:
            throw logic_error("Invalid " + string(1, curr) + " symbol at line " + to_string(line_number));
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (begin_pos != end_pos)
        tokens.emplace_back(PqlToken(type, token, line_number));
    begin_pos = end_pos;
}

void pql::PqlTokenizer::processConstInteger(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& tokens
) {
    size_t size = source.size(), end_pos;

    for (end_pos = begin_pos + 1; end_pos < size; end_pos++) {
        char curr = source[end_pos];

        if (!isdigit(curr)) break;
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (begin_pos != end_pos)
        tokens.emplace_back(PqlToken(TokenType::kConstantInteger, token, line_number));
    begin_pos = end_pos;
}

void pql::PqlTokenizer::processConstString(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& tokens
) {
    size_t size = source.size(), end_pos;
    bool found = false;

    for (end_pos = begin_pos + 1; end_pos < size; end_pos++) {
        char curr = source[end_pos];

        if (curr == '"') {
            end_pos++;
            found = true;
            break;
        }
    }

    if (found) {
        string token = source.substr(begin_pos, end_pos - begin_pos);
        tokens.emplace_back(PqlToken(TokenType::kConstantString, token, line_number));
    }
    begin_pos = end_pos;
}

void pql::PqlTokenizer::processName(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& tokens
) {
    size_t size = source.size(), end_pos;
    TokenType type = TokenType::kIdentifier;
    char curr;

    for (end_pos = begin_pos; end_pos < size; end_pos++) {
        curr = source[end_pos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (token == "such" && source.substr(begin_pos, 9) == "such that") {
        type = TokenType::kKeyWord;
        token = "such that";
        end_pos = begin_pos + 9;
    }

    if (PqlToken::keyword_set.find(token) != PqlToken::keyword_set.end()) {
        type = TokenType::kKeyWord;

        if (curr == '*' && (token == "Follows" || token == "Parent")) {
            token += '*';
            end_pos++;
        }
    }

    if (begin_pos != end_pos)
        tokens.emplace_back(PqlToken(type, token, line_number));
    begin_pos = end_pos;
}
