
#ifndef GUARD_VAR_TABLE_H
#define GUARD_VAR_TABLE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

using std::unordered_map;
using std::vector;
using std::string;

typedef string VAR_NAME;
typedef vector<string> LIST_OF_VAR_NAME;
typedef int VAR_INDEX;

class VarTable {
public:
    static VAR_INDEX addVar(VAR_NAME varName);
    static VAR_NAME getVarName(VAR_INDEX index);
    static VAR_INDEX getVarIndex(VAR_NAME varName);
    static LIST_OF_VAR_NAME getAllVarName();
    static int getSize();

private:
    static unordered_map<VAR_INDEX, VAR_NAME> indexToNameMap;
    static unordered_map<VAR_NAME, VAR_INDEX> nameToIndexMap;
    static int size;
};


#endif // GUARD_VAR_TABLE_H