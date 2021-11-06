#ifndef GUARD_NEXT_TABLE_H
#define GUARD_NEXT_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class NextTable : public Table<ProgLine, ProgLine> {
public:
    static NextTable* getInstance() {
        if (nextTablePtr == nullptr) {
            nextTablePtr = new NextTable;
        }
        return nextTablePtr;
    }
    static bool addNext(ProgLine n1, ProgLine n2);
    static bool isNext(ProgLine n1, ProgLine n2);
    static ListOfProgLines getNext(ProgLine n1);
    static ListOfProgLines getPrev(ProgLine n2);
    static const std::unordered_map<ProgLine, ListOfProgLines>& getNextMap();
    static const std::unordered_map<ProgLine, ListOfProgLines>& getPrevMap();
    static void clear();

private:
    static NextTable* nextTablePtr;
    static inline const size_t NEXT_MAP = 1;
    static inline const size_t PREV_MAP = 2;

    NextTable() {
        oneToManyMap[NEXT_MAP] = std::unordered_map<ProgLine, ListOfProgLines>();
        oneToManyRevMap[PREV_MAP] = std::unordered_map<ProgLine, ListOfProgLines>();
    }
};

#endif
