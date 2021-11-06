#include "NextBipTable.h"

NextBipTable* NextBipTable::nextTablePtr = nullptr;

bool NextBipTable::addNext(ProgLine n1, ProgLine n2)
{
    return getInstance()->addOneToMany(NEXT_MAP, n1, n2)
    && getInstance()->addOneToManyRev(PREV_MAP, n2, n1);
}

bool NextBipTable::isNext(ProgLine n1, ProgLine n2)
{
    return getInstance()->isOneToMany(NEXT_MAP, n1, n2);
}

ListOfProgLines NextBipTable::getNext(ProgLine n1)
{
    return getInstance()->getOneToMany(NEXT_MAP, n1);
}

ListOfProgLines NextBipTable::getPrev(ProgLine n2)
{
    return getInstance()->getOneToManyRev(PREV_MAP, n2);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextBipTable::getNextMap()
{
    return getInstance()->getOneToManyMap(NEXT_MAP);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextBipTable::getPrevMap()
{
    return getInstance()->getOneToManyRevMap(PREV_MAP);
}

void NextBipTable::clear()
{
    getInstance()->clearAll();
}
