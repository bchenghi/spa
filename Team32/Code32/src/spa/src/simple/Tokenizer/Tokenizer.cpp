#include "Tokenizer.h"
#include "Token.h"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::isdigit;
using std::isspace;
using std::logic_error;
using std::string;
using std::vector;

vector<simple::Token> simple::Tokenizer::tokenize(string& source)
{
    vector<Token> tokens;
    size_t size = source.size(), pos = 0, line_number = 1;

    while (pos < size) {
        try {
            next(pos, line_number, source, tokens);
        } catch (logic_error& err) {
            // TODO: Handle error
            std::cout << err.what() << std::endl;
            throw err;
        }
    }

    return tokens;
}

void simple::Tokenizer::next(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<Token>& tokens
) {
    using std::isalpha;

    char curr = source[begin_pos];
    size_t size = source.size();

    while (begin_pos < size && isspace(curr)) {
        if (curr == '\n') line_number++;

        curr = source[++begin_pos];
    }

    bool is_const = isdigit(curr), is_name = isalpha(curr);

    if (is_const) {
        processConst(begin_pos, line_number, source, tokens);
        return;
    }
    if (is_name) {
        processName(begin_pos, line_number, source, tokens);
        return;
    }

    processSymbol(begin_pos, line_number, source, tokens);
}

void simple::Tokenizer::processSymbol(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<Token>& tokens
) {
    using std::to_string;

    char curr = source[begin_pos];
    size_t end_pos = begin_pos;
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
            end_pos++;
            type = Token::token_map.find(curr)->second;
            break;

        case '<':
        case '>':
            type = Token::token_map.find(curr)->second;

            if (source[end_pos + 1] == '=') {
                end_pos += 2;
                break;
            }

            end_pos++;
            break;

        case '!':
            if (source[end_pos + 1] == '=') {
                end_pos += 2;
                type = TokenType::kRelationalOperator;
                break;
            }

            end_pos++;
            type = Token::token_map.find(curr)->second;
            break;

        case '&':
            if (source[end_pos + 1] == '&') {
                end_pos += 2;
                type = TokenType::kConditionOperator;
                break;
            }

            throw logic_error("Invalid & symbol at line " + to_string(line_number));

        case '|':
            if (source[end_pos + 1] == '|') {
                end_pos += 2;
                type = TokenType::kConditionOperator;
                break;
            }

            throw logic_error("Invalid | symbol at line " + to_string(line_number));

        case '=':
            if (source[end_pos + 1] == '=') {
                end_pos += 2;
                type = TokenType::kRelationalOperator;
                break;
            }

            end_pos++;
            type = Token::token_map.find(curr)->second;
            break;

        default:
            throw logic_error("Invalid " + string(1, curr) + " symbol at line " + to_string(line_number));
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (begin_pos != end_pos)
        tokens.emplace_back(Token(type, token, line_number));
    begin_pos = end_pos;
}

void simple::Tokenizer::processConst(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), end_pos;

    for (end_pos = begin_pos; end_pos < size; end_pos++) {
        char curr = source[end_pos];

        if (!isdigit(curr)) break;
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (begin_pos != end_pos)
        tokens.emplace_back(Token(TokenType::kConstant, token, line_number));
    begin_pos = end_pos;
}

void simple::Tokenizer::processName(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<Token>& tokens
) {
    size_t size = source.size(), end_pos;
    TokenType type = TokenType::kIdentifier;

    for (end_pos = begin_pos; end_pos < size; end_pos++) {
        char curr = source[end_pos];

        if (!isalnum(curr)) break;
    }

    string token = source.substr(begin_pos, end_pos - begin_pos);

    if (Token::keyword_set.find(token) != Token::keyword_set.end())
        type = TokenType::kKeyWord;

    if (begin_pos != end_pos)
        tokens.emplace_back(Token(type, token, line_number));
    begin_pos = end_pos;
}