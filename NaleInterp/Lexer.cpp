#include "Lexer.h"
#include <iostream>
#define noop

namespace NaleLexer {
	//return 0 if cannot be a keyword
	//return 1 if can be a keyword
	//return 2 if is a keyword
	int keyword_check(std::string presm) {
		for (int i = 0; i < keywords->length(); ++i) {
			if (!(keywords[i].rfind(presm, 0) == 0)) {
				return 0;
			}
			else if (presm == keywords[i]) {
				return 2;
			}
		}
		return 1;
	}

	std::vector<token> lexical_analysis(std::string superstring) {
		// Init vector of chars using string iterators
		const std::vector<char> chrarr(superstring.begin(), superstring.end());
		std::string token_buffer = "";
		std::vector<token> tokens;

		// 0 none
		// 1 number literal writing
		// 2 string literal writing
		// 3 comment
		int execution_context = 0;

		for (int i = 0; i < chrarr.size(); i++) {

			if (execution_context != 2) {
				// In case there are more than one \t or \n in a row
				if (chrarr[i] == ' ' || chrarr[i] == '\t' || chrarr[i] == '\n') {
					continue;
				}
				// If the separator is the first character in the file or after the string literal context switch
				if (chrarr[i] == '{' || chrarr[i] == '(' || chrarr[i] == ')' || chrarr[i] == '}') {
					token t = token(tokentype::separator, std::string(1, chrarr[i]));
					tokens.push_back(t);
					continue;
				}

				token_buffer += chrarr[i];

				// YANDERE DEV FACT: switch cannot be used at strings so dont @ me

				//in-place check if infix operator

				if (token_buffer == "+") {
					token t = token(tokentype::infix_operator, "+");
					tokens.push_back(t);
					token_buffer = "";
					continue;
				}
				else if (token_buffer == "-") {
					token t = token(tokentype::infix_operator, "-");
					tokens.push_back(t);
					token_buffer = "";
					continue;
				}
				else if (token_buffer == "*") {
					token t = token(tokentype::infix_operator, "*");
					tokens.push_back(t);
					token_buffer = "";
					continue;
				}
				else if (token_buffer == "/") {
					token t = token(tokentype::infix_operator, "/");
					tokens.push_back(t);
					token_buffer = "";
					continue;
				}
				else if (token_buffer == "\"") {
					execution_context = 2;
					continue;
				}

				if (i != chrarr.size() - 1) {
					if (chrarr[i + 1] == '{' || chrarr[i + 1] == '(' || chrarr[i + 1] == ')' || chrarr[i + 1] == '}') {
						std::vector<token> recursive_tokens = lexical_analysis(token_buffer);
						for (int k = 0; k < recursive_tokens.size(); k++) {
							tokens.push_back(recursive_tokens[k]);
						}
						token_buffer = "";
						token t = token(tokentype::separator, std::string(1, chrarr[i + 1]));
						tokens.push_back(t);
						if (i != chrarr.size()) {
							i++;
						}
						continue;
					}

					if (chrarr[i] == '?' && chrarr[i + 1] == '?') {
						execution_context = 3;
						token_buffer.pop_back();
						for (int k = i; k < chrarr.size(); k++) {
							if (chrarr[k] == '\n') {
								execution_context = 0;
								i = k;
								break;
							}
						}
						continue;
					}

					if (chrarr[i + 1] == ' ' || chrarr[i + 1] == '\n' || "" + chrarr[i + 1] == "\r\n" || chrarr[i + 1] == '\t') {

						if (execution_context == 1) { //makes switch/case loop skip (just adds i+=1 in default)
							token t = token(tokentype::literal, token_buffer);
							tokens.push_back(t);
							token_buffer = "";
						}

						execution_context = 0;

						int answer = keyword_check(token_buffer);

						switch (answer) {
						case 0: {
								i++;
								token t = token(tokentype::identifier, token_buffer);
								tokens.push_back(t);
								token_buffer = "";
								break;
							}
						case 1: {
								i++;
								token t = token(tokentype::identifier, token_buffer);
								tokens.push_back(t);
								token_buffer = "";
								break;
							}
						case 2: {
								i++;
								token t = token(tokentype::keyword, token_buffer);
								tokens.push_back(t);
								token_buffer = "";
								break;
							}
						default:
							i++;
						}
					}

					if (token_buffer.length() >= 1) {
						if (token_buffer[0] == '0'
							|| token_buffer[0] == '1'
							|| token_buffer[0] == '2'
							|| token_buffer[0] == '3'
							|| token_buffer[0] == '4'
							|| token_buffer[0] == '5'
							|| token_buffer[0] == '6'
							|| token_buffer[0] == '7'
							|| token_buffer[0] == '8'
							|| token_buffer[0] == '9') {
							execution_context = 1;
						}
					}
				}
				else {
					token t = token(tokentype::identifier, token_buffer);
					if (execution_context == 1) {
						t = token(tokentype::literal, token_buffer);
					}
					tokens.push_back(t);
					token_buffer = "";
				}
				
			}
			else {
				if (chrarr[i] != '\"') {
					token_buffer += chrarr[i];
				}
				else {
					execution_context = 0;
					token t = token(tokentype::literal, token_buffer + "\"");
					tokens.push_back(t);
					token_buffer = "";
				}
				
			}

			

		}

		return tokens;

	}
}