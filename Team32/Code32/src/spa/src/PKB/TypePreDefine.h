#ifndef GUARD_TYPE_PRE_DEFINE_H
#define GUARD_TYPE_PRE_DEFINE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef size_t STMT_NO;
typedef size_t VAR_INDEX;
typedef std::string PROC_NAME;
typedef std::string VAR_NAME;
typedef std::vector<std::string> LIST_OF_PROC_NAME;
typedef std::unordered_set<STMT_NO> LIST_OF_STMT_NO;
typedef std::unordered_set<VAR_NAME> LIST_OF_VAR_NAME;
typedef std::unordered_set<int> LIST_OF_CONSTANT;

#endif //GUARD_TYPE_PRE_DEFINE_H
