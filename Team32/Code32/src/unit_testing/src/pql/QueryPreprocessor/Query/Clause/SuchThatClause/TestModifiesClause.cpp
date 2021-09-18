#include "catch.hpp"

#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"

#include <set>

using std::set;
using std::unordered_set;
using std::string;
using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::ModifiesClause;
using pql::FilterResult;

TEST_CASE("Modifies Clause PKB Abstractor query", "[ModifiesClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("Should return matches if both arguments are design entities") {
        // Uses(a, v) where a is assign and v is variable
        // Pkb abs returns {(1, {"a"}), (2, {"a", "b"})}
        // Should return {{(a,1), (v, "a")}, {(a,2), (v, "a")}, {(a,2), (v, "b")}}

        pkbAbsStub.resultValueVarSet = {pair<string, unordered_set<string>>("1", {"a"}), pair<string, unordered_set<string>>("2", {"a", "b"})};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryDesignEntity varV(DesignEntity::Variable, "v");

        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&varV, nullptr, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue stmt2(DesignEntity::Stmt, "2");
        QueryArgValue varA(DesignEntity::Variable, "a");
        QueryArgValue varB(DesignEntity::Variable, "b");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1), pair<QueryDesignEntity, QueryArgValue>(varV, varA)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2), pair<QueryDesignEntity, QueryArgValue>(varV, varA)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2), pair<QueryDesignEntity, QueryArgValue>(varV, varB)}};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryDesignEntity assignA(DesignEntity::Assign, "a");

        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, nullptr, true);
        ModifiesClause modifiesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue stmt2(DesignEntity::Stmt, "2");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2)}};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArgValue variableVar(DesignEntity::Variable, "var");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue stmt2(DesignEntity::Stmt, "2");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1)},
                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2)}};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(&variableV, nullptr, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::Variable, "var");
        QueryArgValue variableVar1(DesignEntity::Variable, "var1");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                 {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        ModifiesClause modifiesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue variableVar(DesignEntity::Variable, "var");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&variableV, nullptr, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::Variable, "var");
        QueryArgValue variableVar1(DesignEntity::Variable, "var1");
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet =
                {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                 {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(nullptr, nullptr, true);
        ModifiesClause modifiesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
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
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryArgValue variableVar(DesignEntity::Variable, "var");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(nullptr, &variableVar, false);
        ModifiesClause modifiesClause(firstArg, secondArg);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>>  expectedSet = {};

        FilterResult obtainedFilterResult = modifiesClause.executePKBAbsQuery(&pkbAbsStub);
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet;
        for (int i = 0; i < obtainedFilterResult.getSize(); i++) {
            obtainedSet.insert(obtainedFilterResult.getEntitiesAndValuesAtIndex(i));
        }

        REQUIRE((obtainedSet == expectedSet && obtainedFilterResult.getHasMatch()));
    }
}

TEST_CASE("Modifies Clause Semantic errors", "[ModifiesClause]") {
    SECTION("Should throw error if first argument is a wildcard") {
        // Modifies(_, "abc")
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a wildcard");
    }

    SECTION("Should throw error if first argument is a variable") {
        // Modifies(v, "abc") where v is a variable
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a variable or constant");
    }

    SECTION("Should throw error if first argument is a constant") {
        // Modifies(c, "abc") where c is a constant.
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a variable or constant");
    }

    SECTION("should throw error if second argument is not a variable") {
        // Modifies(s, p) where s is Stmt and p is Procedure
        QueryArgValue procedureValueAbc(DesignEntity::Procedure, "abc");
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        QueryArg firstArg(&stmtS, nullptr, false);
        QueryArg secondArg(nullptr, &procedureValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: Second argument must be a variable");
    }
}
