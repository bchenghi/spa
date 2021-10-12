#include "NextTable.h"

std::unordered_map<ProgLine, ListOfProgLines> NextTable::nextMap;
std::unordered_map<ProgLine, ListOfProgLines> NextTable::prevMap;

bool NextTable::addNext(ProgLine n1, ProgLine n2) 
{
    auto res1 = NextTable::nextMap.find(n1);
    auto res2 = NextTable::prevMap.find(n2);
    if (res1 != NextTable::nextMap.end()) {
        NextTable::nextMap[n1].insert(n2);
        if (res2 != NextTable::prevMap.end()) {
            NextTable::prevMap[n2].insert(n1);
        }
        else {
            NextTable::prevMap[n2] = ListOfProgLines();
            NextTable::prevMap[n2].insert(n1);
        }
        return true;
    }
    else {
        NextTable::nextMap[n1] = ListOfProgLines();
        NextTable::nextMap[n1].insert(n2);
        if (res2 != NextTable::prevMap.end()) {
            NextTable::prevMap[n2].insert(n1);
        }
        else {
            NextTable::prevMap[n2] = ListOfProgLines();
            NextTable::prevMap[n2].insert(n1);
        }
        return true;
    }
    return false;
}

bool NextTable::isNext(ProgLine n1, ProgLine n2)
{
    auto res = NextTable::nextMap.find(n1);
    if (res != NextTable::nextMap.end()) {
        if (res->second.count(n2)) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

ListOfProgLines NextTable::getNext(ProgLine n1)
{
    auto res = NextTable::nextMap.find(n1);
    if (res != NextTable::nextMap.end()) {
        return res->second;
    }
    else {
        return ListOfProgLines();
    }
}

ListOfProgLines NextTable::getPrev(ProgLine n2)
{
    auto res = NextTable::prevMap.find(n2);
    if (res != NextTable::prevMap.end()) {
        return res->second;
    }
    else {
        return ListOfProgLines();
    }
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getNextMap()
{
    return nextMap;
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getPrevMap()
{
    return prevMap;
}

void NextTable::clear()
{
    nextMap.clear();
    prevMap.clear();
}
