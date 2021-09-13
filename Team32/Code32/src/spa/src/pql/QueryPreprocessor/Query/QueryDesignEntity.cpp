#include "QueryDesignEntity.h"

using pql::DesignEntity;
using pql::QueryDesignEntity;

QueryDesignEntity::QueryDesignEntity(DesignEntity designEntity, std::string variableName)
: designEntity(designEntity), variableName(variableName) {
}

bool QueryDesignEntity::operator==(const QueryDesignEntity& other) const {
    if (designEntity == other.designEntity && variableName == other.variableName) {
        return true;
    }
    return false;
}

bool QueryDesignEntity::operator <( const QueryDesignEntity& k) const {
    if (designEntity < k.designEntity) {
        return true;
    } else if (designEntity == k.designEntity) {
        return variableName < k.variableName;
    } else {
        return false;
    }
}


