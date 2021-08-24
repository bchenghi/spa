#include "SimpleTokenizer.h"

#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<SimpleToken> SimpleTokenizer::tokenize(string& source) {
    vector<SimpleToken> result;

    return result;
}

void SimpleTokenizer::next(size_t& begin_pos, size_t& line_number, string& source, vector<SimpleToken>& result) {
    using std::isspace;

}
