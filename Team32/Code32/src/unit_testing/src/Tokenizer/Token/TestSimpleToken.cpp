#include "catch.hpp"
#include "Tokenizer/Token/SimpleToken.h"

#include <string>

using simple::SimpleToken;
using simple::TokenType;
using std::string;

TEST_CASE("SimpleToken", "[simple]") {
    int kLineNumber = 148;
    string kKeyword = "procedure";
    SimpleToken token(TokenType::kKeyWord, kKeyword, kLineNumber);

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
