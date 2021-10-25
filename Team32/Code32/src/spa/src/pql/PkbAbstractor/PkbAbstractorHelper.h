#ifndef GUARD_PKB_ABSTRACTOR_HELPER_H
#define GUARD_PKB_ABSTRACTOR_HELPER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <utility>
#include <algorithm>
#include "../src/pql/DesignEntity.h"
#include "../src/pql/AttributeType.h"

typedef size_t StmtNum;
typedef size_t ProcLine;
typedef std::string VarName;
typedef std::string ProcName;
typedef std::string Value;
typedef std::vector<std::string> PostFixExpression;
typedef std::vector<std::vector<size_t>> Graph;

using std::string;
using std::list;
using std::pair;
using std::unordered_set;
using std::unordered_map;

namespace pql {
    class PkbAbstractorHelper {
    public:

        static bool isNum(const std::string&);

        // Uses
        static list<pair<string, unordered_set<VarName>>> usesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesPrintHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesCallHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> usesProcNameHelper(const string&, const VarName&);

        // Modifies
        static list<pair<string, unordered_set<VarName>>> modifiesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesReadHelper(const VarName& varName);
        static list<pair<string, unordered_set<VarName>>> modifiesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesCallHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> modifiesProcNameHelper(const string&, const VarName&);

        // Assign pattern
        static list<pair<StmtNum, VarName>> getAssignPatternAllStmts(const Value& value, PostFixExpression postFixExpression, bool hasUnderscores);
        static list<pair<StmtNum, VarName>> getAssignPatternSpecificStmt(StmtNum, const Value& value, PostFixExpression postFixExpression, bool hasUnderscores);

        // While pattern
        static list<pair<StmtNum, unordered_set<VarName>>> getWhilePatternAllStmts(const Value& value);
        static list<pair<StmtNum, unordered_set<VarName>>> getWhilePatternSpecificStmt(StmtNum, const Value& value);

        // If pattern
        static list<pair<StmtNum, unordered_set<VarName>>> getIfPatternAllStmts(const Value& value);
        static list<pair<StmtNum, unordered_set<VarName>>> getIfPatternSpecificStmt(StmtNum, const Value& value);

        // With
        static list<pair<Value, Value>> getWithNoneValues(DesignEntity, AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperAssign1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperCall1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperConstant1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperIf1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperPrint1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperProcedure1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperStmtOrProgline1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperRead1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperVariable1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperWhile1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithOneValue(DesignEntity, AttributeType, const Value& value2);
        static list<pair<Value, Value>> getWithBothValues(const Value& value1, const Value& value2);

        // NextStar
        static Graph initGraph(int);
        static Graph createNextStarGraph();
        static std::unordered_set<ProcLine> getNextStar(ProcLine, Graph);
        static std::unordered_set<ProcLine> getPrevStar(ProcLine, Graph);

        // Affects
        static bool isSameProc(StmtNum, StmtNum);
        static bool isModifiesUsed(StmtNum, StmtNum);
        static bool isAffectsItself(StmtNum, VarName);
        static list<std::vector<StmtNum>> getAllPaths(StmtNum, StmtNum);
        static void getAllPathsHelper(StmtNum, StmtNum, std::vector<size_t>&, std::vector<StmtNum>&, list<std::vector<StmtNum>>&);
        static bool isStmtModifiesVar(StmtNum, VarName);
        static bool isVarNotModifiedByAPath(list<std::vector<StmtNum>>, VarName);
        static bool isAffects(StmtNum, StmtNum);

        // AffectsStar
        static Graph createAffectsStarGraph();
        static std::unordered_set<StmtNum> getAffectsStar(StmtNum, Graph);
        static std::unordered_set<StmtNum> getAffectedByStar(StmtNum, Graph);

        // Graphs map
        static std::unordered_map<Value, Graph> graphsMap;
        static Graph getGraph(Value);
        static void addGraph(Value, Graph);
        static void clearGraphs();
    };
}

#endif //AUTOTESTER_PKB_ABSTRACTOR_HELPER_H
