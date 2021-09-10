#include "ParserUtils.h"

#include <stdexcept>
#include <string>

using std::string;
using std::to_string;
using std::logic_error;

void throwWithoutToken(string expectedToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected at line " + to_string(lineNumber));
}

void throwWithToken(string expectedToken, string actualToken, size_t lineNumber)
{
    throw logic_error(expectedToken + " expected instead of '"
        + actualToken + "' at line " + to_string(lineNumber));
}
