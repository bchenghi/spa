#include "QueryDesignEntity.h"

#include <utility>
#include "SyntaxCheck.h"

using pql::AttributeType;
using pql::DesignEntity;
using pql::QueryDesignEntity;
using pql::SemanticError;

QueryDesignEntity::QueryDesignEntity() : designEntity(), variableName(), attributeType() {

}

QueryDesignEntity::QueryDesignEntity(DesignEntity designEntity, std::string variableName, AttributeType attributeType)
    : designEntity(designEntity), variableName(std::move(variableName)), attributeType(attributeType) {
    if (attributeType != AttributeType::NONE) {
        if (attributeType == AttributeType::VARIABLE_NAME && designEntity != DesignEntity::VARIABLE &&
        designEntity != DesignEntity::PRINT && designEntity != DesignEntity::READ) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query Design Entity: Invalid attribute type for design entity");
        } else if (attributeType == AttributeType::PROCEDURE_NAME && designEntity != DesignEntity::CALL &&
        designEntity != DesignEntity::PROCEDURE) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query Design Entity: Invalid attribute type for design entity");
        } else if (attributeType == AttributeType::STMT_NUM && designEntity != DesignEntity::STMT &&
        designEntity != DesignEntity::READ && designEntity != DesignEntity::PRINT &&
        designEntity != DesignEntity::CALL && designEntity != DesignEntity::WHILE &&
        designEntity != DesignEntity::IF && designEntity != DesignEntity::ASSIGN) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query Design Entity: Invalid attribute type for design entity");
        } else if (attributeType == AttributeType::VALUE && designEntity != DesignEntity::CONSTANT) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query Design Entity: Invalid attribute type for design entity");
        }
    }
}

bool QueryDesignEntity::operator==(const QueryDesignEntity& other) const {
    if (designEntity == other.designEntity && variableName == other.getVariableName()) {
        return true;
    }
    return false;
}

bool QueryDesignEntity::operator!=(const QueryDesignEntity& other) const {
    return !(*this == other);
}

bool QueryDesignEntity::operator <( const QueryDesignEntity& k) const {
    if (designEntity < k.designEntity) {
        return true;
    } else if (designEntity == k.designEntity) {
        return variableName < k.getVariableName();
    } else {
        return false;
    }
}

DesignEntity QueryDesignEntity::getDesignEntity() const {
    return designEntity;
}

std::string QueryDesignEntity::getVariableName() const {
    return variableName;
}

AttributeType QueryDesignEntity::getAttributeType() const {
    return attributeType;
}
