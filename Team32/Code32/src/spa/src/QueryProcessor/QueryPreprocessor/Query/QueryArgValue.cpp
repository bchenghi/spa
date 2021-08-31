#include "QueryArgValue.h"

#include <string>

QueryArgValue::QueryArgValue(DesignEntity designEntity, std::string value) {
    if (designEntity != DesignEntity::Stmt && designEntity != DesignEntity::Variable && designEntity != DesignEntity::Procedure) {
        throw "QueryArgValue: Design entity type not valid";
    }
    designEntity = designEntity;
    value = value;
}

bool QueryArgValue::operator==(const QueryArgValue &other) const {
    if (designEntity == other.designEntity && value == other.value) {
        return true;
    }
    return false;
}
