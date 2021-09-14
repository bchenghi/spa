#include "TestWrapper.h"
#include "simple/SourceProcessor/Parser.h"
#include "pql/QueryProcessorManager.h"
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "pql/QueryPreprocessor/Preprocessor.h"
#include "pql/QueryResultProjector/QueryResultProjector.h"

#include <fstream>
#include <set>
#include <string>
#include <streambuf>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0) wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename)
{
    using simple::Parser;
    using std::fstream;
    using std::istreambuf_iterator;
    using std::string;

    Parser parser;
    fstream file(filename);
    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    parser.parse(source);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results)
{
    using std::set;
    using pql::QueryProcessorManager;

    QueryProcessorManager queryProcessorManager;

    set<string> res = queryProcessorManager.executeQuery(query);

    for (const string& s : res)
        results.push_back(s);
}

TestWrapper::~TestWrapper() = default;
