#pragma once
#include <string>
namespace Nale {
	enum class tokentype {
		none,
		possbile_token,

		identifier,
		infix_operator,
		separator,
		literal,
		keyword
	};

	std::string lookup_tokentype_enum(tokentype t);

	struct token {
		token();
		token(tokentype type, std::string value);

		tokentype type;
		std::string value;
	};
}
