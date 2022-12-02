#include <iostream>
#include "Lexer.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: lang2 <file>" << std::endl;
		std::exit(1);
	}

	std::ifstream t(argv[1]);
	std::string str((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());

	Lang::Lexer lexer(str);

	lexer.lex();

	return 0;
}
