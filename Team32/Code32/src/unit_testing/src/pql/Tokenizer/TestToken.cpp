#include "catch.hpp"

#include "pql/Tokenizer/Token.h"

#include <string>

using pql::Token;
using pql::TokenType;
using std::string;

TEST_CASE("pql::Token", "[pql]") {
    int kLineNumber = 8;
    string kKeyword = "variable";
    Token token(TokenType::kKeyWord, kKeyword, kLineNumber);

    SECTION("should get line number from token") {
        REQUIRE(token.GetLineNumber() == kLineNumber);
    }

    SECTION("should get token type from token") {
        REQUIRE(token.GetTokenType() == TokenType::kKeyWord);
    }

    SECTION("should get actual token from token") {
        REQUIRE(token.GetToken() == kKeyword);
    }
}
