#include "simple/Tokenizer/Token.h"
#include "ParserUtils.h"

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::logic_error;
using std::string;
using std::to_string;
using std::isspace;

void throwWithoutToken(const string& expectedToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected at line " + to_string(lineNumber));
}

void throwWithToken(const string& expectedToken, const string& actualToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected instead of '"
        + actualToken + "' at line " + to_string(lineNumber));
}

std::vector<string> tokenToPostfixExpression(
    const std::vector<simple::Token>& tokens,
    size_t startIndex,
    size_t endIndex
) {
    using simple::Token;
    using simple::TokenType;
    using std::stack;
    using std::string;
    using std::unordered_map;
    using std::vector;

    static unordered_map<string, size_t> precedence = {
            { "*", 3 },
            { "/", 3 },
            { "%", 3 },
            { "+", 2 },
            { "-", 2 },
            { "(", 1 }
    };

    vector<string> postfixList;
    size_t i;
    stack<Token> opStack;

    for (i = startIndex; i < endIndex; i++) {
        const Token& token = tokens[i];
        Token topToken;

        switch (token.getTokenType()) {
            case TokenType::NAME:
            case TokenType::CONSTANT:
                postfixList.emplace_back(token.getToken());
                break;

            case TokenType::OPEN_BRACKET:
                opStack.push(token);
                break;

            case TokenType::CLOSE_BRACKET:
                topToken = opStack.top();
                opStack.pop();

                while (topToken.getTokenType() != TokenType::OPEN_BRACKET) {
                    postfixList.emplace_back(topToken.getToken());
                    topToken = opStack.top();
                    opStack.pop();
                }

                break;

            default:
                while (!opStack.empty() && (precedence[opStack.top().getToken()] >= precedence[token.getToken()])) {
                    postfixList.emplace_back(opStack.top().getToken());
                    opStack.pop();
                }

                opStack.push(token);
                break;
        }
    }

    while (!opStack.empty()) {
        postfixList.emplace_back(opStack.top().getToken());
        opStack.pop();
    }

    return postfixList;
}

void throwWithMessage(const string& message) {
    throw std::logic_error(message);
}

void ltrim(string& source)
{
    source.erase(
        source.begin(),
        std::find_if(
            source.begin(),
            source.end(),
            [](unsigned char c) { return !std::isspace(c); }
        )
    );
}

void rtrim(string& source)
{
    source.erase(
        std::find_if(
            source.rbegin(),
            source.rend(),
            [](unsigned char c) { return !isspace(c); }
        ).base(),
        source.end()
    );
}

void trim(string& source)
{
    ltrim(source);
    rtrim(source);
}
