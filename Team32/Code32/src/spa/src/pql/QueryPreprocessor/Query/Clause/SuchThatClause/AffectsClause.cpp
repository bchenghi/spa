#include "AffectsClause.h"

using pql::AffectsClause;

AffectsClause::AffectsClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {}
