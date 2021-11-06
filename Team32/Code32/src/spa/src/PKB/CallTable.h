#ifndef GUARD_CALL_TABLE_H
#define GUARD_CALL_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class CallTable : public Table<ProcName, ProcName> {
public:
    static CallTable* getInstance() {
        if (callTablePtr == nullptr) {
            callTablePtr = new CallTable;
        }
        return callTablePtr;
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
    static CallTable* callTablePtr;
    static inline const size_t CALL_MAP = 1;
    static inline const size_t CALL_REV_MAP = 2;
    static inline const size_t CALL_STAR_MAP = 3;
    static inline const size_t CALL_STAR_REV_MAP = 4;

    CallTable() {
        oneToManyMap[CALL_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        oneToManyRevMap[CALL_REV_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        oneToManyMap[CALL_STAR_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
        oneToManyRevMap[CALL_STAR_REV_MAP] = std::unordered_map<ProcName, ListOfProcNames>();
    }
};

#endif
