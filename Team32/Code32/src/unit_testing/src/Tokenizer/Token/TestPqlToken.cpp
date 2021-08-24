#include "Tokenizer/Token/PqlToken.h"
#include "catch.hpp"

using pql::PqlToken;
using pql::TokenType;

TEST_CASE("PqlToken", "[pql]") {
    PqlToken token(TokenType::kKeyWord, "variable", 8);

    SECTION("should get line number from token") {
        REQUIRE(token.GetLineNumber() == 8);
    }

    SECTION("should get token type from token") {
        REQUIRE(token.GetTokenType() == TokenType::kKeyWord);
    }

    SECTION("should get actual token from token") {
        REQUIRE(token.GetToken() == "variable");
    }
}
