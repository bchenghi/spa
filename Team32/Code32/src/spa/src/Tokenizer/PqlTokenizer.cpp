#include "PqlTokenizer.h"

#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<PqlToken> PqlTokenizer::tokenize(string& source)
{
    vector<PqlToken> result;

    return result;
}

void PqlTokenizer::next(
    size_t& begin_pos,
    size_t& line_number,
    string& source,
    vector<PqlToken>& result
) {
    using std::isspace;

}
