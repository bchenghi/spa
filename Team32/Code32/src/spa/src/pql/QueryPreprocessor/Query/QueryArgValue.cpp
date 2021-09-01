#include "QueryArgValue.h"

#include <string>

using pql::DesignEntity;
using pql::QueryArgValue;

QueryArgValue::QueryArgValue(DesignEntity designEntity, std::string value)
: designEntity(designEntity), value(value) {
    if (designEntity != DesignEntity::Stmt && designEntity != DesignEntity::Variable && designEntity != DesignEntity::Procedure) {
        throw "QueryArgValue: Design entity type not valid";
    }
    designEntity = designEntity;
    value = value;
}

bool QueryArgValue::operator==(const QueryArgValue& other) const {
    if (designEntity == other.designEntity && value == other.value) {
        return true;
    }
    return false;
}
