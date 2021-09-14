#include "TestWrapper.h"
#include "simple/SourceProcessor/Parser.h"
#include "pql/QueryPreprocessor/Preprocessor.h"

#include <fstream>
#include <string>
#include <streambuf>
#include <set>
#include <pql/QueryResultProjector/QueryResultProjector.h>
#include <pql/QueryEvaluator/QueryEvaluator.h>

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
    using std::cout;
    using std::endl;
    using std::string;
    using std::istreambuf_iterator;
    simple::Parser parser;

    std::fstream file(filename);
    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        parser.parse(source);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results)
{
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...

    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
    pql::Preprocessor preprocessor;

    pql::Query pqlQuery = preprocessor.preprocess(query);
    pql::QueryResultProjector queryResultProjector;
    pql::PkbAbstractor pkbAbstractor;
    pql::QueryEvaluator qe(&pkbAbstractor, &queryResultProjector);

    std::set<string> res = qe.executeQuery(pqlQuery);

    for (const string& s : res) {
        results.push_back(s);
        cout << s << ",";
    }
}

TestWrapper::~TestWrapper() = default;
