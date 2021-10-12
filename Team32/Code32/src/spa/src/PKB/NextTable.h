#ifndef GUARD_NEXT_TABLE_H
#define GUARD_NEXT_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class NextTable {
public:
    static bool addNext(ProgLine n1, ProgLine n2);
    static bool isNext(ProgLine n1, ProgLine n2);
    static ListOfProgLines getNext(ProgLine n1);
    static ListOfProgLines getPrev(ProgLine n2);
    static const std::unordered_map<ProgLine, ListOfProgLines>& getNextMap();
    static const std::unordered_map<ProgLine, ListOfProgLines>& getPrevMap();
    static void clear();

private:
    static std::unordered_map<ProgLine, ListOfProgLines> nextMap;
    static std::unordered_map<ProgLine, ListOfProgLines> prevMap;
};

#endif // GUARD_NEXT_TABLE_H
