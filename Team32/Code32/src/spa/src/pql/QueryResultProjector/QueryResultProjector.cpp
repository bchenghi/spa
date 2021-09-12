#include "QueryResultProjector.h"
#include <iostream>

using pql::QueryResultProjector;
using std::cout;

std::string QueryResultProjector::outputResult(std::vector<std::string> results) {
    for (std::string result : results) {
        cout << result;
        cout << "\n";
    }
    return "";
}
