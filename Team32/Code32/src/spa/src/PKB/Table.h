#ifndef GUARD_TABLE_H
#define GUARD_TABLE_H

#include "TypePreDefine.h"

template <class T, class U>
class Table {
protected:
    std::unordered_map<size_t, std::unordered_map<T, U>> one_to_one_map;
    std::unordered_map<size_t, std::unordered_map<U, T>> one_to_one_rev_map;

    std::unordered_map<size_t, std::unordered_map<T, std::unordered_set<U>>> one_to_many_map;
    std::unordered_map<size_t, std::unordered_map<U, std::unordered_set<T>>> one_to_many_rev_map;

    bool add_one_to_one(size_t map_name, T a, U b) {
        check_one_to_one_map(map_name);
        one_to_one_map[map_name][a] = b;
        return true;
    }

    bool add_one_to_one_rev(size_t map_name, U b, T a) {
        check_one_to_one_rev_map(map_name);
        one_to_one_rev_map[map_name][b] = a;
        return true;
    }

    bool add_one_to_many(size_t map_name, T a, std::unordered_set<U> b) {
        check_one_to_many_map(map_name);
        auto res = one_to_many_map[map_name].find(a);
        if (res != one_to_many_map[map_name].end()) {
            throw "Undefined.";
        }
        one_to_many_map[map_name][a] = b;
        return true;
    }

    bool add_one_to_many(size_t map_name, T a, U b) {
        check_one_to_many_map(map_name);
        one_to_many_map[map_name][a].insert(b);
        return true;
    }

    bool add_one_to_many_rev(size_t map_name, U b, std::unordered_set<T> a) {
        check_one_to_many_rev_map(map_name);
        auto res = one_to_many_rev_map[map_name].find(b);
        if (res != one_to_many_rev_map[map_name].end()) {
            throw "Undefined.";
        }
        one_to_many_rev_map[map_name][b] = a;
        return true;
    }

    bool add_one_to_many_rev(size_t map_name, U b, T a) {
        check_one_to_many_rev_map(map_name);
        one_to_many_rev_map[map_name][b].insert(a);
        return true;
    }

    bool is_one_to_one(size_t map_name, T a, U b) {
        check_one_to_one_map(map_name);
        return one_to_one_map[map_name][a] == b;
    }

    bool is_one_to_one_empty(size_t map_name, T a) {
        check_one_to_one_map(map_name);
        return one_to_one_map[map_name].count(a) == 0;
    }

    bool is_one_to_one_rev_empty(size_t map_name, U b) {
        check_one_to_one_rev_map(map_name);
        return one_to_one_rev_map[map_name].count(b) == 0;
    }

    bool is_one_to_many(size_t map_name, T a, U b) {
        check_one_to_many_map(map_name);
        return one_to_many_map[map_name].count(a) && one_to_many_map[map_name][a].count(b) > 0;
    }

    bool is_one_to_many_empty(size_t map_name, T a) {
        check_one_to_many_map(map_name);
        return one_to_many_map[map_name].count(a) == 0;
    }

    bool is_one_to_many_rev_empty(size_t map_name, U b) {
        check_one_to_many_rev_map(map_name);
        return one_to_many_rev_map[map_name].count(b) == 0;
    }

    const U get_one_to_one(size_t map_name, T a) {
        check_one_to_one_map(map_name);
        return one_to_one_map[map_name][a];
    }

    const T get_one_to_one_rev(size_t map_name, U b) {
        check_one_to_one_rev_map(map_name);
        return one_to_one_rev_map[map_name][b];
    }

    const std::unordered_map<T, U>& get_one_to_one_map(size_t map_name) {
        check_one_to_one_map(map_name);
        return one_to_one_map[map_name];
    }

    const std::unordered_map<U, T>& get_one_to_one_rev_map(size_t map_name) {
        check_one_to_one_rev_map(map_name);
        return one_to_one_rev_map[map_name];
    }

    const std::unordered_set<U> get_one_to_many(size_t map_name, T a) {
        check_one_to_many_map(map_name);
        if (one_to_many_map[map_name].count(a)) {
            return one_to_many_map[map_name][a];
        }
        else {
            return std::unordered_set<U>();
        }
    }

    const std::unordered_set<T> get_one_to_many_rev(size_t map_name, U b) {
        check_one_to_many_rev_map(map_name);
        if (one_to_many_rev_map[map_name].count(b)) {
            return one_to_many_rev_map[map_name][b];
        }
        else {
            return std::unordered_set<T>();
        }
    }

    const std::unordered_map<T, std::unordered_set<U>>& get_one_to_many_map(size_t map_name) {
        check_one_to_many_map(map_name);
        return one_to_many_map[map_name];
    }

    const std::unordered_map<U, std::unordered_set<T>>& get_one_to_many_rev_map(size_t map_name) {
        check_one_to_many_rev_map(map_name);
        return one_to_many_rev_map[map_name];
    }

    void clearAll() {
        for (auto iter = one_to_one_map.begin(); iter != one_to_one_map.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = one_to_one_rev_map.begin(); iter != one_to_one_rev_map.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = one_to_many_map.begin(); iter != one_to_many_map.end(); ++iter) {
            iter->second.clear();
        }

        for (auto iter = one_to_many_rev_map.begin(); iter != one_to_many_rev_map.end(); ++iter) {
            iter->second.clear();
        }
    }

    void check_one_to_one_map(size_t map_name) {
        if (one_to_one_map.count(map_name) == 0) {
            throw "This 1-1 MAP does not exist.";
        }
    }

    void check_one_to_one_rev_map(size_t map_name) {
        if (one_to_one_rev_map.count(map_name) == 0) {
            throw "This 1-1-r MAP does not exist.";
        }
    }

    void check_one_to_many_map(size_t map_name) {
        if (one_to_many_map.count(map_name) == 0) {
            throw "This 1-m MAP does not exist.";
        }
    }

    void check_one_to_many_rev_map(size_t map_name) {
        if (one_to_many_rev_map.count(map_name) == 0) {
            throw "This 1-m-r MAP does not exist.";
        }
    }
};

#endif // GUARD_TABLE_H
