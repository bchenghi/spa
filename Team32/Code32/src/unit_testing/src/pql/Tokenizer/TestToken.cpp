#include "catch.hpp"

#include "pql/Tokenizer/Token.h"

#include <string>

using pql::Token;
using pql::TokenType;
using std::string;

TEST_CASE("pql::Token", "[pql]") {
    int kLineNumber = 8;
    string kKeyword = "variable";
    Token token(TokenType::KEY_WORD, kKeyword, kLineNumber);

    SECTION("should get line number from token") {
        REQUIRE(token.getLineNumber() == kLineNumber);
    }

    SECTION("should get token type from token") {
        REQUIRE(token.getTokenType() == TokenType::KEY_WORD);
    }

    SECTION("should get actual token from token") {
        REQUIRE(token.getToken() == kKeyword);
    }
}
