#include "catch.hpp"
#include "Tokenizer/Token/PqlToken.h"

#include <string>

using pql::PqlToken;
using pql::TokenType;
using std::string;

TEST_CASE("PqlToken", "[pql]") {
    int kLineNumber = 8;
    string kKeyword = "variable";
    PqlToken token(TokenType::kKeyWord, kKeyword, kLineNumber);

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
