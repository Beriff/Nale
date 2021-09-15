#pragma once
#include "Token.h"
#include "Tree.h"
using namespace Nale;

namespace NaleLexer {
	const std::string keywords[] = {"using", "scope", "package", "func", "int", "str", "float", "bool", "true", "false", "func"};
	int keyword_check(std::string presm);

	std::vector<Nale::token> lexical_analysis(std::string superstring);
}