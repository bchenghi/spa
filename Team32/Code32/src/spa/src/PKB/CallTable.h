#ifndef GUARD_CALL_TABLE_H
#define GUARD_CALL_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class CallTable : public Table<ProcName, ProcName> {
public:
    static CallTable* getInstance() {
        if (call_table_ptr == nullptr) {
            call_table_ptr = new CallTable;
        }
        return call_table_ptr;
    }
    static bool addCall(ProcName proc1, ProcName proc2);
    static bool addCallStar(ProcName proc1, ProcName proc2);
    static bool isCall(ProcName proc1, ProcName proc2);
    static bool isCallStar(ProcName proc1, ProcName proc2);
    static ListOfProcNames getCall(ProcName proc1);
    static ListOfProcNames getCalledBy(ProcName proc2);
    static ListOfProcNames getCallStar(ProcName proc1);
    static ListOfProcNames getCalledStarBy(ProcName proc2);
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallReverseMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallStarMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallStarReverseMap();
    static void clear();

private:
    //static std::unordered_map<ProcName, ListOfProcNames> callMap;
    //static std::unordered_map<ProcName, ListOfProcNames> reverseCallMap;
    //static std::unordered_map<ProcName, ListOfProcNames> callStarMap;
    //static std::unordered_map<ProcName, ListOfProcNames> reverseCallStarMap;

    static CallTable* call_table_ptr;
    static inline const size_t CALL_MAP = 1;
    static inline const size_t CALL_REV_MAP = 2;
    static inline const size_t CALL_STAR_MAP = 3;
    static inline const size_t CALL_STAR_REV_MAP = 4;

    CallTable() {
        one_to_many_map[CALL_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        one_to_many_rev_map[CALL_REV_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        one_to_many_map[CALL_STAR_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        one_to_many_rev_map[CALL_STAR_REV_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
    }
};

#endif // GUARD_CALL_TABLE_H
