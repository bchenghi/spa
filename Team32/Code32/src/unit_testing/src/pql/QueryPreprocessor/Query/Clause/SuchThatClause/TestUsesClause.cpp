#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/UsesClause.h"

#include <set>

using std::set;
using std::unordered_set;
using std::string;
using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::UsesClause;
using pql::FilterResult;
using pql::SemanticError;

TEST_CASE("Uses Clause PKB Abstractor query", "[UsesClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("Should return matches if both arguments are design entities") {
        // Uses(a, v) where a is assign and v is variable
        // Pkb abs returns {(1, {"a"}), (2, {"a", "b"})}
        // Should return {{(a,1), (v, "a")}, {(a,2), (v, "a")}, {(a,2), (v, "b")}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"a"}), pair<string, unordered_set<string>>("2", {"a", "b"})};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity varV(DesignEntity::VARIABLE, "v");

        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&varV, nullptr, false);
        UsesClause usesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        QueryArgValue varA(DesignEntity::VARIABLE, "a");
        QueryArgValue varB(DesignEntity::VARIABLE, "b");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1), pair<QueryDesignEntity, QueryArgValue>(varV, varA)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2), pair<QueryDesignEntity, QueryArgValue>(varV, varA)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2), pair<QueryDesignEntity, QueryArgValue>(varV, varB)}};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a design entity and second is a wildcard") {
        // Uses(a, _) where a is assign
        // Pkb abs returns {(1, {"a"}), (2, {"a", "b"})}
        // Should return {{(a,1)}, {(a,2)}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"a"}), pair<string, unordered_set<string>>("2", {"a", "b"})};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");

        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, nullptr, true);
        UsesClause usesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2)}};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a design entity and second is a variable name") {
        // Uses(a, "var") where a is assign
        // Pkb abs returns {(1, {"var"}), (2, {"var"})}
        // Should return {{(a,1)}, {(a,2)}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"var"}), pair<string, unordered_set<string>>("2", {"var", "b"})};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        UsesClause usesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2)}};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a stmt num and second is a design entity") {
        // Uses(1, v) where v is variable
        // Pkb abs returns {(1, {"var", "var1"})}
        // Should return {{(v,"var")}, {(v,"var1")}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"var", "var1"})};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(&variableV, nullptr, false);
        UsesClause usesClause(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                 {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a stmt num and second is a wildcard") {
        // Uses(1, _)
        // Pkb abs returns {(1, {"var", "var1"})}
        // Should return {}, has match is true

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"var", "var1"})};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        UsesClause usesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a stmt num and second is a variable name") {
        // Uses(1, "var")
        // Pkb abs returns {(1, {"var"})}
        // Should return {}, has match is true

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"var"})};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        UsesClause usesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a procedure name and second is a design entity") {
        // Uses("main", v)
        // Pkb abs returns {("main", {"var", "var1"})}
        // Should return {{(v,"var")}, {(v,"var1")}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("main", {"var", "var1"})};
        QueryArgValue procedureMain(DesignEntity::PROCEDURE, "main");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&variableV, nullptr, false);
        UsesClause usesClause(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                 {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a procedure name and second is a wildcard") {
        // Uses("main", _)
        // Pkb abs returns {("main", {"var", "var1"})}
        // Should return {}, has match is true

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("main", {"var", "var1"})};
        QueryArgValue procedureMain(DesignEntity::PROCEDURE, "main");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(nullptr, nullptr, true);
        UsesClause usesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }

    SECTION("Should return matches if first argument is a procedure name and second is a variable name") {
        // Uses("main", "var")
        // Pkb abs returns {("main", {"var"})}
        // Should return {}, has match is true

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("main", {"var"})};
        QueryArgValue procedureMain(DesignEntity::PROCEDURE, "main");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        UsesClause usesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = usesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }
}

TEST_CASE("Uses Clause semantic errors", "[UsesClause]") {
    SECTION("Should throw error if first argument is a wildcard") {
        // Uses(_, "abc")
        QueryArgValue variableValueAbc(DesignEntity::VARIABLE, "abc");
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_AS(UsesClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a variable") {
        // Uses(v, "abc") where v is a variable
        QueryArgValue variableValueAbc(DesignEntity::VARIABLE, "abc");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_AS(UsesClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a constant") {
        // Uses(c, "abc") where c is a constant.
        QueryArgValue variableValueAbc(DesignEntity::VARIABLE, "abc");
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_AS(UsesClause(firstArg, secondArg), SemanticError);
    }

    SECTION("should throw error if second argument is not a variable") {
        // Uses(s, p) where s is Stmt and p is Procedure
        QueryDesignEntity procedureAbc(DesignEntity::PROCEDURE, "abc");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryArg firstArg(&stmtS, nullptr, false);
        QueryArg secondArg(&procedureAbc, nullptr, false);
        REQUIRE_THROWS_AS(UsesClause(firstArg, secondArg), SemanticError);
    }
}
