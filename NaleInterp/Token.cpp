#include "Token.h"

namespace Nale {
	std::string lookup_tokentype_enum(tokentype t) {
		switch (t) {
		case tokentype::identifier: { return "identifier"; };
		case tokentype::infix_operator: { return "infix_op"; };
		case tokentype::literal: { return "literal"; };
		case tokentype::keyword: { return "keyword"; };
		case tokentype::separator: { return "separator"; };
		default: { return "none"; };
		}
	}

	token::token(tokentype type, std::string value) {
		this->type = type;
		this->value = value;
	}
}