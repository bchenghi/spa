#include "catch.hpp"

#include "simple/Tokenizer/Token.h"

#include <string>

using simple::Token;
using simple::TokenType;
using std::string;

TEST_CASE("simple::Token", "[simple]") {
    int kLineNumber = 148;
    string kKeyword = "procedure";
    Token token(TokenType::NAME, kKeyword, kLineNumber);

    SECTION("should get line number from token") {
        REQUIRE(token.getLineNumber() == kLineNumber);
    }

    SECTION("should get token type from token") {
        REQUIRE(token.getTokenType() == TokenType::NAME);
    }

    SECTION("should get actual token from token") {
        REQUIRE(token.getToken() == kKeyword);
    }
}
