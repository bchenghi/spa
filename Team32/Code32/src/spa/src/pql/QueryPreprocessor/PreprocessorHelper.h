#include "Query/Query.h"
#include "../Tokenizer/Token.h"
#include "../Tokenizer/Tokenizer.h"

namespace pql {
	enum class ClauseType {
		Follows,
		FollowsStar,
		Modifies,
		Parent,
		ParentStar,
		Uses,
		None
	};

	class PreprocessorHelper {
	public:
		static pql::DesignEntity get_design_entity(pql::Token token);
		static bool parse_design_entity(
			std::vector<pql::Token>& token_list,
			std::vector<pql::QueryDesignEntity>& design_entities);
		static bool parse_select_clause(
			std::vector<pql::Token>& token_list,
			pql::SelectClause*& select,
			std::vector<pql::QueryDesignEntity>& design_entities);
		static bool parse_filters(
			std::vector<pql::Token>& token_list, 
			std::vector<pql::FilterClause*>& filters, 
			std::vector<pql::QueryDesignEntity>& design_entities);
		static pql::ClauseType get_clause_type(pql::Token token);
		static pql::QueryArg get_query_arg(
			pql::Token token,
			std::vector<pql::QueryDesignEntity>& design_entities);

		static inline const std::unordered_map<std::string, pql::DesignEntity> design_entity_map = {
			{ "stmt", pql::DesignEntity::Stmt },
			{ "read", pql::DesignEntity::Read },
			{ "print", pql::DesignEntity::Print },
			{ "call", pql::DesignEntity::Call },
			{ "while", pql::DesignEntity::While },
			{ "if", pql::DesignEntity::If },
			{ "assign", pql::DesignEntity::Assign },
			{ "variable", pql::DesignEntity::Variable },
			{ "constant", pql::DesignEntity::Constant },
			{ "procedure", pql::DesignEntity::Procedure }
		};

		static inline const std::unordered_map<std::string, pql::ClauseType> clause_type_map = {
			{ "Follows", pql::ClauseType::Follows },
			{ "Follows*", pql::ClauseType::FollowsStar },
			{ "Modifies", pql::ClauseType::Modifies },
			{ "Parent", pql::ClauseType::Parent },
			{ "Parent*", pql::ClauseType::ParentStar },
			{ "Uses", pql::ClauseType::Uses }
		};
	};
}