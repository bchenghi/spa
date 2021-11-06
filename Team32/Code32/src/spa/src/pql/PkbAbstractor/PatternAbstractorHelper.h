#ifndef GUARD_PATTERN_ABSTRACTOR_HELPER_H
#define GUARD_PATTERN_ABSTRACTOR_HELPER_H

namespace pql {
    class PatternAbstractorHelper {
    public:
        static list<pair<StmtNum, VarName>> getAssignPatternAllStmtsSubMatch(const Value&, PostFixExpression);
        static list<pair<StmtNum, VarName>> getAssignPatternAllStmtsFullMatch(const Value&, PostFixExpression);
        static list<pair<StmtNum, VarName>> getAssignPatternSpecificStmtSubMatch(StmtNum, const Value&, PostFixExpression);
        static list<pair<StmtNum, VarName>> getAssignPatternSpecificStmtFullMatch(StmtNum, const Value&, PostFixExpression);

        static list<pair<StmtNum, unordered_set<VarName>>> getWhilePatternAllStmts(const Value&);
        static list<pair<StmtNum, unordered_set<VarName>>> getWhilePatternSpecificStmt(StmtNum, const Value&);

        static list<pair<StmtNum, unordered_set<VarName>>> getIfPatternAllStmts(const Value&);
        static list<pair<StmtNum, unordered_set<VarName>>> getIfPatternSpecificStmt(StmtNum, const Value&);
    };
}

#endif
