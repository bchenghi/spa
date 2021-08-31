#include "QueryDesignEntity.h"

QueryDesignEntity::QueryDesignEntity(DesignEntity designEntity, std::string variableName) {
    designEntity = designEntity;
    variableName = variableName;
}
bool QueryDesignEntity::operator==(const QueryDesignEntity & other) const {
    if (designEntity == other.designEntity && variableName == other.variableName) {
        return true;
    }
    return false;
}
