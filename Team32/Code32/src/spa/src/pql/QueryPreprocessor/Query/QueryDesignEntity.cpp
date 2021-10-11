#include "QueryDesignEntity.h"

#include <utility>

using pql::DesignEntity;
using pql::QueryDesignEntity;

QueryDesignEntity::QueryDesignEntity(DesignEntity designEntity, std::string variableName, AttributeType attributeType)
    : designEntity(designEntity), variableName(std::move(variableName)), attributeType(attributeType) {
    if (attributeType != AttributeType::NONE) {
        if (attributeType == AttributeType::VARIABLE_NAME && designEntity != DesignEntity::VARIABLE &&
        designEntity != DesignEntity::PRINT && designEntity != DesignEntity::READ) {
            throw "Invalid attribute type for design entity";
        } else if (attributeType == AttributeType::PROCEDURE_NAME && designEntity != DesignEntity::CALL &&
        designEntity != DesignEntity::PROCEDURE) {
            throw "Invalid attribute type for design entity";
        } else if (attributeType == AttributeType::STMT_NUM && designEntity != DesignEntity::STMT &&
        designEntity != DesignEntity::READ && designEntity != DesignEntity::PRINT &&
        designEntity != DesignEntity::CALL && designEntity != DesignEntity::WHILE &&
        designEntity != DesignEntity::IF && designEntity != DesignEntity::ASSIGN) {
            throw "Invalid attribute type for design entity";
        } else if (attributeType == AttributeType::VALUE && designEntity != DesignEntity::CONSTANT) {
            throw "Invalid attribute type for design entity";
        }
    }
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


