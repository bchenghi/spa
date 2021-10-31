#ifndef GUARD_PREPROCESSOR_HELPER_H
#define GUARD_PREPROCESSOR_HELPER_H
#include "Query/Query.h"
#include "../Tokenizer/Token.h"
#include "../Tokenizer/Tokenizer.h"
#include "Query/SyntaxCheck.h"

namespace pql {
    class PreprocessorHelper {
    public:
        static bool parse_design_entity(
            std::vector<pql::Token>& tokenList,
            std::vector<pql::QueryDesignEntity>& designEntities
        );
        static bool parse_select_clause(
            std::vector<pql::Token>& tokenList,
            pql::SelectClause*& select,
            std::vector<pql::QueryDesignEntity>& designEntities
        );
        static bool parse_filters(
            std::vector<pql::Token>& token_list, 
            std::vector<pql::FilterClause*>& filters, 
            std::vector<pql::QueryDesignEntity>& designEntities,
            std::string &last_clause
        );

        static inline const std::unordered_map<std::string, pql::DesignEntity> designEntityMap = {
            { "stmt", pql::DesignEntity::STMT },
            { "read", pql::DesignEntity::READ },
            { "print", pql::DesignEntity::PRINT },
            { "call", pql::DesignEntity::CALL },
            { "while", pql::DesignEntity::WHILE },
            { "if", pql::DesignEntity::IF },
            { "assign", pql::DesignEntity::ASSIGN },
            { "variable", pql::DesignEntity::VARIABLE },
            { "constant", pql::DesignEntity::CONSTANT },
            { "procedure", pql::DesignEntity::PROCEDURE },
            { "prog_line", pql::DesignEntity::PROGRAM_LINE }
        };

        static inline const std::unordered_map<std::string, pql::ClauseType> clauseTypeMap = {
            { "Follows", pql::ClauseType::FOLLOWS },
            { "Follows*", pql::ClauseType::FOLLOWSSTAR },
            { "Modifies", pql::ClauseType::MODIFIES },
            { "Parent", pql::ClauseType::PARENT },
            { "Parent*", pql::ClauseType::PARENTSTAR },
            { "Uses", pql::ClauseType::USES },
            { "Calls", pql::ClauseType::CALLS },
            { "Calls*", pql::ClauseType::CALLSSTAR },
            { "Next", pql::ClauseType::NEXT },
            { "Next*", pql::ClauseType::NEXTSTAR },
            { "Affects", pql::ClauseType::AFFECTS },
            { "Affects*", pql::ClauseType::AFFECTSSTAR }
        };

        static inline const std::unordered_map<std::string, pql::AttributeType> attrTypeMap = {
                { "procName", pql::AttributeType::PROCEDURE_NAME},
                { "varName", pql::AttributeType::VARIABLE_NAME},
                { "value", pql::AttributeType::VALUE},
                { "stmt#", pql::AttributeType::STMT_NUM}
        };
    };
}
#endif
