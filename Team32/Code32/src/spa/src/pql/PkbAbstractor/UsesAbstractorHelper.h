#ifndef GUARD_USES_ABSTRACTOR_HELPER_H
#define GUARD_USES_ABSTRACTOR_HELPER_H

typedef std::string VarName;
typedef size_t StmtNum;

using std::list;
using std::pair;
using std::unordered_set;

namespace pql {
    class UsesAbstractorHelper {
    public:
        static list<pair<string, unordered_set<VarName>>> usesDesignEntityHelper(DesignEntity, const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtNumHelper(StmtNum, const VarName&);
        static list<pair<string, unordered_set<ProcName>>> usesProcNameHelper(const string&, const VarName&);

    private:
        static list<pair<string, unordered_set<VarName>>> usesAssignHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesStmtHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesPrintHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesWhileHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesIfHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesProcHelper(const VarName&);
        static list<pair<string, unordered_set<VarName>>> usesCallHelper(const VarName&);
    };
}

#endif
