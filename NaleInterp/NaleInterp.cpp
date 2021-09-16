// NaleInterp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "Lexer.h"

int main()
{
    std::ifstream t("C:\\Users\\Maxim\\Desktop\\nale_runtime\\nale.nale");
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::vector<token> tokens = NaleLexer::lexical_analysis(buffer.str());

    for (int i = 0; i < tokens.size(); i++) {
        std::cout << '[' << tokens[i].value << " : " << Nale::lookup_tokentype_enum(tokens[i].type) << ']' << std::endl;
    }
}

