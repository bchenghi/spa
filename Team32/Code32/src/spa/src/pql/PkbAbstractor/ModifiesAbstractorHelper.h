#ifndef GUARD_MODIFIES_ABSTRACTOR_HELPER_H
#define GUARD_MODIFIES_ABSTRACTOR_HELPER_H

namespace pql {
    class ModifiesAbstractorHelper {
    public:
        static list<pair<string, unordered_set<VarName>>> modifiesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> modifiesProcNameHelper(const string&, const VarName&);

    private:
        static list<pair<string, unordered_set<VarName>>> modifiesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesReadHelper(const VarName& varName);
        static list<pair<string, unordered_set<VarName>>> modifiesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> modifiesCallHelper(const VarName&);
    };
}

#endif
