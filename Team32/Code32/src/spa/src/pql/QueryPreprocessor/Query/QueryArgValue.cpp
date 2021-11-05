#include "QueryArgValue.h"

#include <string>

using pql::DesignEntity;
using pql::QueryArgValue;

QueryArgValue::QueryArgValue(DesignEntity designEntity, std::string value)
        : designEntity(designEntity), value(value)
{
    if (designEntity != DesignEntity::STMT && designEntity != DesignEntity::VARIABLE &&
    designEntity != DesignEntity::PROCEDURE && designEntity != DesignEntity::CONSTANT) {
        // Not an error by semantic or syntactic rules
        throw "QueryArgValue: Design entity type not valid";
    }
}

bool QueryArgValue::operator==(const QueryArgValue& other) const {
    if (designEntity == other.getDesignEntity() && value == other.getValue()) {
        return true;
    }
    return false;
}

bool QueryArgValue::operator <(const QueryArgValue& k) const {
    if (designEntity < k.getDesignEntity()) {
        return true;
    } else if (designEntity == k.getDesignEntity()) {
        return value < k.value;
    } else {
        return false;
    }
}

DesignEntity QueryArgValue::getDesignEntity() const {
    return designEntity;
};

std::string QueryArgValue::getValue() const {
    return value;
}

void QueryArgValue::setDesignEntity(DesignEntity newDesignEntity) {
    designEntity = newDesignEntity;
}
