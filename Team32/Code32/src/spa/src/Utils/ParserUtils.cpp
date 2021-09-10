#include "simple/Tokenizer/Token.h"
#include "ParserUtils.h"

#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::logic_error;
using std::string;
using std::to_string;

void throwWithoutToken(string expectedToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected at line " + to_string(lineNumber));
}

void throwWithToken(string expectedToken, string actualToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected instead of '"
        + actualToken + "' at line " + to_string(lineNumber));
}

string join(const std::vector<string>& strings, char delimiter)
{
    string result;
    size_t i, size = strings.size();

    for (i = 0; i < size; i++) {
        result += strings[i];

        if (i < size) result += delimiter;
    }

    return result;
}

string tokenToPostfixExpression(
    const std::vector<simple::Token>& tokens,
    size_t startIndex,
    size_t endIndex
) {
    using std::stack;
    using std::string;
    using simple::Token;
    using simple::TokenType;
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

        switch (token.GetTokenType()) {
            case TokenType::kIdentifier:
            case TokenType::kConstant:
                postfixList.emplace_back(token.GetToken());
                break;

            case TokenType::kOpenBracket:
                opStack.push(token);
                break;

            case TokenType::kCloseBracket:
                topToken = opStack.top();
                opStack.pop();

                while (topToken.GetTokenType() != TokenType::kOpenBracket) {
                    postfixList.emplace_back(topToken.GetToken());
                    topToken = opStack.top();
                    opStack.pop();
                }

                break;

            default:
                while (!opStack.empty() && (precedence[opStack.top().GetToken()] >= precedence[token.GetToken()])) {
                    postfixList.emplace_back(opStack.top().GetToken());
                    opStack.pop();
                }

                opStack.push(token);
                break;
        }
    }

    while (!opStack.empty()) {
        postfixList.emplace_back(opStack.top().GetToken());
        opStack.pop();
    }

    return join(postfixList, ' ');
}
