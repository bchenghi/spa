#ifndef GUARD_TABLE_H
#define GUARD_TABLE_H

#include "TypePreDefine.h"

template <class T, class U>
class Table {
protected:
    std::unordered_map<size_t, std::unordered_map<T, U>> oneToOneMap;
    std::unordered_map<size_t, std::unordered_map<U, T>> oneToOneRevMap;

    std::unordered_map<size_t, std::unordered_map<T, std::unordered_set<U>>> oneToManyMap;
    std::unordered_map<size_t, std::unordered_map<U, std::unordered_set<T>>> oneToManyRevMap;

    bool addOneToOne(size_t mapId, T a, U b) {
        checkOneToOneMap(mapId);
        oneToOneMap[mapId][a] = b;
        return true;
    }

    bool addOneToOneRev(size_t mapId, U b, T a) {
        checkOneToOneRevMap(mapId);
        oneToOneRevMap[mapId][b] = a;
        return true;
    }

    bool addOneToMany(size_t mapId, T a, std::unordered_set<U> b) {
        checkOneToManyMap(mapId);
        auto res = oneToManyMap[mapId].find(a);
        if (res != oneToManyMap[mapId].end()) {
            throw "Undefined.";
        }
        oneToManyMap[mapId][a] = b;
        return true;
    }

    bool addOneToMany(size_t mapId, T a, U b) {
        checkOneToManyMap(mapId);
        oneToManyMap[mapId][a].insert(b);
        return true;
    }

    bool addOneToManyRev(size_t mapId, U b, std::unordered_set<T> a) {
        checkOneToManyRevMap(mapId);
        auto res = oneToManyRevMap[mapId].find(b);
        if (res != oneToManyRevMap[mapId].end()) {
            throw "Undefined.";
        }
        oneToManyRevMap[mapId][b] = a;
        return true;
    }

    bool addOneToManyRev(size_t mapId, U b, T a) {
        checkOneToManyRevMap(mapId);
        oneToManyRevMap[mapId][b].insert(a);
        return true;
    }

    bool isOneToOne(size_t mapId, T a, U b) {
        checkOneToOneMap(mapId);
        return oneToOneMap[mapId][a] == b;
    }

    bool isOneToOneEmpty(size_t mapId, T a) {
        checkOneToOneMap(mapId);
        return oneToOneMap[mapId].count(a) == 0;
    }

    bool isOneToOneRevEmpty(size_t mapId, U b) {
        checkOneToOneRevMap(mapId);
        return oneToOneRevMap[mapId].count(b) == 0;
    }

    bool isOneToMany(size_t mapId, T a, U b) {
        checkOneToManyMap(mapId);
        return oneToManyMap[mapId].count(a) && oneToManyMap[mapId][a].count(b) > 0;
    }

    bool isOneToManyEmpty(size_t mapId, T a) {
        checkOneToManyMap(mapId);
        return oneToManyMap[mapId].count(a) == 0;
    }

    bool isOneToManyRevEmpty(size_t mapId, U b) {
        checkOneToManyRevMap(mapId);
        return oneToManyRevMap[mapId].count(b) == 0;
    }

    U getOneToOne(size_t mapId, T a) {
        checkOneToOneMap(mapId);
        return oneToOneMap[mapId][a];
    }

    T getOneToOneRev(size_t mapId, U b) {
        checkOneToOneRevMap(mapId);
        return oneToOneRevMap[mapId][b];
    }

    const std::unordered_map<T, U>& getOneToOneMap(size_t mapId) {
        checkOneToOneMap(mapId);
        return oneToOneMap[mapId];
    }

    const std::unordered_map<U, T>& getOneToOneRevMap(size_t mapId) {
        checkOneToOneRevMap(mapId);
        return oneToOneRevMap[mapId];
    }

    std::unordered_set<U> getOneToMany(size_t mapId, T a) {
        checkOneToManyMap(mapId);
        if (oneToManyMap[mapId].count(a)) {
            return oneToManyMap[mapId][a];
        }
        else {
            return std::unordered_set<U>();
        }
    }

    std::unordered_set<T> getOneToManyRev(size_t mapId, U b) {
        checkOneToManyRevMap(mapId);
        if (oneToManyRevMap[mapId].count(b)) {
            return oneToManyRevMap[mapId][b];
        }
        else {
            return std::unordered_set<T>();
        }
    }

    const std::unordered_map<T, std::unordered_set<U>>& getOneToManyMap(size_t mapId) {
        checkOneToManyMap(mapId);
        return oneToManyMap[mapId];
    }

    const std::unordered_map<U, std::unordered_set<T>>& getOneToManyRevMap(size_t mapId) {
        checkOneToManyRevMap(mapId);
        return oneToManyRevMap[mapId];
    }

    void clearAll() {
        for (auto iter = oneToOneMap.begin(); iter != oneToOneMap.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = oneToOneRevMap.begin(); iter != oneToOneRevMap.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = oneToManyMap.begin(); iter != oneToManyMap.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = oneToManyRevMap.begin(); iter != oneToManyRevMap.end(); ++iter) {
            iter->second.clear();
        }
    }

    void checkOneToOneMap(size_t mapId) {
        if (oneToOneMap.count(mapId) == 0) {
            throw "This 1-1 MAP does not exist.";
        }
    }

    void checkOneToOneRevMap(size_t mapId) {
        if (oneToOneRevMap.count(mapId) == 0) {
            throw "This 1-1-r MAP does not exist.";
        }
    }

    void checkOneToManyMap(size_t mapId) {
        if (oneToManyMap.count(mapId) == 0) {
            throw "This 1-m MAP does not exist.";
        }
    }

    void checkOneToManyRevMap(size_t mapId) {
        if (oneToManyRevMap.count(mapId) == 0) {
            throw "This 1-m-r MAP does not exist.";
        }
    }
};

#endif // GUARD_TABLE_H
